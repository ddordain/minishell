/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_master.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:36:29 by pwu               #+#    #+#             */
/*   Updated: 2022/04/19 15:07:09 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_builtin(char *cmd)
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

static void	wait_one(t_command *cmd)
{
	int	status;

	if (waitpid(cmd->pid, &status, 0) == -1)
		perror("waitpid()");
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = 128 + WTERMSIG(status);
}

static void	prep_next_cmd(t_elem *cur_elem)
{
	t_command	*cur_cmd;
	t_command	*prev_cmd;

	cur_cmd = cur_elem->data;
	prev_cmd = NULL;
	if (cur_elem->prev)
		prev_cmd = cur_elem->prev->data;
	ft_close(&cur_cmd->pipefd[PIPE_WR]);
	ft_close(&cur_cmd->here_doc);
	if (cur_elem->next == NULL)
		ft_close(&cur_cmd->pipefd[PIPE_RD]);
	if (prev_cmd)
		ft_close(&prev_cmd->pipefd[PIPE_RD]);
}

static void	wait_all(t_minishell *sh)
{
	t_elem		*cur_elem;
	t_command	*cur_cmd;

	cur_elem = sh->dl_cmd.head;
	while (cur_elem != NULL)
	{
		cur_cmd = cur_elem->data;
		wait_one(cur_cmd);
		cur_elem = cur_elem->next;
	}
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
			return (exec_in_parent(cur_elem, cur_cmd));
		if (cur_elem->next != NULL)
			if (pipe(cur_cmd->pipefd) == -1)
				return (pre_exec_error("pipe()", sh), 1);
		cur_cmd->pid = fork();
		if (cur_cmd->pid == -1)
			return (pre_exec_error("fork()", sh), 1);
		if (cur_cmd->pid == 0)
			exec_cmd(cur_elem, sh);
		else
			prep_next_cmd(cur_elem);
		cur_elem = cur_elem->next;
	}
	wait_all(sh);
	return (0);
}
