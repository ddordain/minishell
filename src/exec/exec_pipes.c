/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 15:13:13 by pwu               #+#    #+#             */
/*   Updated: 2022/04/20 12:18:53 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	exec_pipe_in(t_elem *elem, t_command *cmd)
{
	t_command	*prev_cmd;

	if (elem->prev != NULL)
	{
		prev_cmd = elem->prev->data;
		if (dup2(prev_cmd->pipefd[PIPE_RD], STDIN_FILENO) == -1)
			return (perror("dup2"), -1);
		if (ft_close(&prev_cmd->pipefd[PIPE_RD]) == -1)
			return (-1);
	}
	if (dup2(cmd->fdin, STDIN_FILENO) == -1)
		return (perror("dup2"), -1);
	if (cmd->fdin == cmd->here_doc)
		cmd->here_doc = -2;
	if (ft_close(&cmd->fdin) == -1)
		return (-1);
	return (0);
}

static int	exec_pipe_out(t_elem *elem, t_command *cmd)
{
	if (elem->next != NULL)
	{
		if (dup2(cmd->pipefd[PIPE_WR], STDOUT_FILENO) == -1)
			return (perror("dup2"), -1);
		if (ft_close(&cmd->pipefd[PIPE_WR]) == -1)
			return (-1);
		if (ft_close(&cmd->pipefd[PIPE_RD]) == -1)
			return (-1);
	}
	if (dup2(cmd->fdout, STDOUT_FILENO) == -1)
		return (perror("dup2"), -1);
	if (ft_close(&cmd->fdout) == -1)
		return (-1);
	return (0);
}

int	exec_pipe(t_elem *elem, t_command *cmd)
{
	if (exec_pipe_in(elem, cmd) != 0)
		return (exec_close_fds(elem), -1);
	if (exec_pipe_out(elem, cmd) != 0)
		return (exec_close_fds(elem), -1);
	return (0);
}
