/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:00:52 by pwu               #+#    #+#             */
/*   Updated: 2022/04/12 19:00:10 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

unsigned char	g_exit_status = 0;

static void	minishell_read(t_line *cmdline, t_minishell *sh)
{
	signal_handler(HANDLER_RL, sh);
	cmdline->line = readline(PROMPT);
	if (!cmdline->line)
		return ;
	cmdline->len = ft_strlen(cmdline->line);
	if (cmdline->len > 0)
		add_history(cmdline->line);
	cmdline->i = 0;
}

static int	minishell_start(t_minishell *sh)
{
	int	err_code;

	err_code = lex(sh);
	if (err_code != 0)
	{
		ft_dlist_destroy(&sh->dl_tok);
		return (err_code);
	}
	parse(sh);
	debug_print_tok(&sh->dl_tok);
	make_cmds(sh);
	ft_dlist_destroy(&sh->dl_tok);
	debug_print_cmd(&sh->dl_cmd);
	err_code = minishell_exec(sh);
	if (err_code != 0)
	{
		ft_dlist_destroy(&sh->dl_cmd);
		return (err_code);
	}
	ft_dlist_destroy(&sh->dl_cmd);
	return (0);
}

static int	minishell_init(t_minishell *sh, char **envp)
{
	signal_handler(HANDLER_MAIN, sh);
	ft_dlist_init(&sh->dl_cmd, cmd_destroy);
	ft_dlist_init(&sh->dl_env, free);
	ft_dlist_init(&sh->dl_tok, free);
	ft_dlist_init(&sh->dl_malloc, free);
	sh->cmdline.line = NULL;
	set_env(sh, envp);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	sh;

	(void)ac;
	(void)av;
	if (!isatty(0) || !isatty(1) || minishell_init(&sh, envp) != 0)
		return (EXIT_FAILURE);
	debug_print_env(&sh.dl_env);
	while (1)
	{
		minishell_read(&sh.cmdline, &sh);
		if (!sh.cmdline.line)
			break ;
		if (minishell_start(&sh) == -1)
			perror_exit("minishell", &sh);
		free(sh.cmdline.line);
	}
	ft_dlist_destroy(&sh.dl_env);
	ft_dlist_destroy(&sh.dl_malloc);
	rl_clear_history();
	echo_on();
	return (g_exit_status);
}
