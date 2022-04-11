/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_master.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:36:29 by pwu               #+#    #+#             */
/*   Updated: 2022/04/11 17:56:22 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if (ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "unset") == 0)
		return (true);
	return (false);
}

static int	exec_in_parent(t_command *cmd, t_dlist *dl_env)
{
	(void)cmd;
	(void)dl_env;
	// add redir
	// if (ft_strcmp(cmd->av[0], "cd") == 0)
	// 	return (builtin_cd(dl_env, cmd));
	return (0);
}

static void	wait_cmd(t_elem *cur_elem)
{
	int			status;
	t_command	*cur_cmd;
	t_command	*prev_cmd;

	cur_cmd = cur_elem->data;
	prev_cmd = NULL;
	if (cur_elem->prev)
		prev_cmd = cur_elem->prev->data;
	waitpid(cur_cmd->pid, &status, 0);
	ft_close(&cur_cmd->pipefd[PIPE_WR]);
	if (cur_elem->next == NULL)
		ft_close(&cur_cmd->pipefd[PIPE_RD]);
	if (prev_cmd)
		ft_close(&prev_cmd->pipefd[PIPE_RD]);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
}

int	minishell_exec(t_minishell *sh)
{
	t_elem		*cur_elem;
	t_command	*cur_cmd;

	cur_elem = sh->dl_cmd.head;
	while (cur_elem != NULL)
	{
		cur_cmd = cur_elem->data;
		if (sh->dl_cmd.size == 1 && is_builtin(cur_cmd->av[0]))
			return (exec_in_parent(cur_cmd, &sh->dl_env));
		if (cur_elem->next != NULL)
			if (pipe(cur_cmd->pipefd) == -1)
				pre_exec_error("pipe()", sh);
		cur_cmd->pid = fork();
		if (cur_cmd->pid == -1)
			pre_exec_error("fork()", sh);
		if (cur_cmd->pid == 0)
			exec_cmd(cur_elem, sh); // update signal for child
		else
			wait_cmd(cur_elem);
		cur_elem = cur_elem->next;
	}
	return (0);
}
