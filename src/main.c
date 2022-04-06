/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:00:52 by pwu               #+#    #+#             */
/*   Updated: 2022/04/06 17:28:55 by pwu              ###   ########.fr       */
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

static int	minishell_start(t_minishell *sh)
{
	int	err_code;

	err_code = lex(&sh->cmdline, &sh->dl_tok, sh);
	if (err_code != 0)
	{
		ft_dlist_destroy(&sh->dl_tok);
		return (err_code);
	}
	if (parse(&sh->dl_tok, &sh->dl_env, sh) != 0)
		return (-1);
	debug_print_tok(&sh->dl_tok);
	if (make_cmds(&sh->dl_tok, &sh->dl_cmd, sh) != 0)
		return (-1);
	ft_dlist_destroy(&sh->dl_tok);
	// err_code = minishell_exec(sh);
	// if (err_code != 0)
	// {
	// 	ft_dlist_destroy(&sh->dl_cmd);
	// 	return (err_code);
	// }
	debug_print_cmd(&sh->dl_cmd);
	ft_dlist_destroy(&sh->dl_cmd);
	return (0);
}

void	free_cmd(void *data)
{
	t_command	*cmd;

	cmd = data;
	if (cmd)
	{
		ft_dlist_destroy(&cmd->redir);
		free(cmd);
	}
}

static int	minishell_init(t_minishell *sh, char **envp)
{
	ft_dlist_init(&sh->dl_cmd, free_cmd);
	ft_dlist_init(&sh->dl_env, free);
	ft_dlist_init(&sh->dl_tok, free);
	ft_dlist_init(&sh->dl_malloc, free);
	if (set_env(&sh->dl_env, envp, sh) != 0)
	{
		ft_dlist_destroy(&sh->dl_env);
		return (-1);
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	sh;

	(void)ac;
	(void)av;
	if (!isatty(0) || !isatty(1) || minishell_init(&sh, envp) != 0)
		return (EXIT_FAILURE);
	// builtin_export(&sh.dl_env, ac, av);
	// builtin_unset(&sh.dl_env, ac, av);
	debug_print_env(&sh.dl_env);
	while (1)
	{
		minishell_read(&sh.cmdline);
		if (!sh.cmdline.line)
			break ;
		if (minishell_start(&sh) == -1)
			perror_exit(NULL, &sh);
		free(sh.cmdline.line);
	}
	ft_dlist_destroy(&sh.dl_env);
	ft_dlist_destroy(&sh.dl_malloc);
	rl_clear_history();
	return (EXIT_SUCCESS);
}
