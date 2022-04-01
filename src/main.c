/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:00:52 by pwu               #+#    #+#             */
/*   Updated: 2022/04/01 15:46:35 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

unsigned char	g_exit_status = 0;

static void	minishell_read(t_line *cmdline)
{
	cmdline->line = readline(PROMPT);
	if (!cmdline->line)
		return ;
	cmdline->len = ft_strlen(cmdline->line);
	if (cmdline->len > 0)
		add_history(cmdline->line);
	cmdline->i = 0;
}

static int	minishell_start(t_line *cmdline, t_minishell *sh)
{
	int	err_code;

	err_code = lex(cmdline, &sh->dl_tok);
	if (err_code != 0)
	{
		ft_dlist_destroy(&sh->dl_tok);
		return (err_code);
	}
	if (parse(&sh->dl_tok, &sh->dl_env) != 0)
	{
		ft_dlist_destroy(&sh->dl_tok);
		return (-1);
	}
	if (make_cmds(&sh->dl_tok, &sh->dl_cmd) != 0)
	{
		ft_dlist_destroy(&sh->dl_tok);
		return (-1);
	}
	debug_print_tok(&sh->dl_tok);
	debug_print_cmd(&sh->dl_cmd);
	ft_dlist_destroy(&sh->dl_tok);
	ft_dlist_destroy(&sh->dl_cmd);
	return (0);
}

static int	minishell_init(t_minishell *sh, char **envp)
{
	ft_dlist_init(&sh->dl_cmd, cmd_destroy);
	ft_dlist_init(&sh->dl_env, env_var_destroy);
	ft_dlist_init(&sh->dl_tok, tok_destroy);
	if (set_env(&sh->dl_env, envp) != 0)
	{
		ft_dlist_destroy(&sh->dl_env);
		return (-1);
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_line		cmdline;
	t_minishell	sh;

	(void)ac;
	(void)av;
	if (!isatty(0) || !isatty(1) || minishell_init(&sh, envp) != 0)
		return (EXIT_FAILURE);
	debug_print_env(&sh.dl_env);
	while (1)
	{
		minishell_read(&cmdline);
		if (!cmdline.line)
			break ;
		if (minishell_start(&cmdline, &sh) == -1)
			perror_exit(NULL, &sh, &cmdline);
		free(cmdline.line);
	}
	ft_dlist_destroy(&sh.dl_env);
	rl_clear_history();
	return (EXIT_SUCCESS);
}
