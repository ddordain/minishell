/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:04:29 by pwu               #+#    #+#             */
/*   Updated: 2022/04/11 13:29:33 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	redir_one(t_command *cmd, t_redir *redir, int *prev_fd)
{
	ft_close(*prev_fd);
	*prev_fd = -2;
	if (redir->type == REDIR_IN)
	{
		cmd->fdin = open(redir->var, O_RDONLY);
		*prev_fd = cmd->fdin;
	}
	if (redir->type == REDIR_TRUNC)
	{
		cmd->fdout = open(redir->var, O_CREAT | O_WRONLY | O_TRUNC);
		*prev_fd = cmd->fdout;
	}
	// if (redir->type == REDIR_HEREDOC || redir->type == REDIR_HEREDOC_RAW)
		//heredoc function
	if (redir->type == REDIR_APPEND)
	{
		cmd->fdout = open(redir->var, O_CREAT | O_WRONLY | O_APPEND);
		*prev_fd = cmd->fdout;
	}
	if (*prev_fd == -1)
		return (perror(redir->var), close_pipes(cmd), -1);
	return (0);
}

static int	exec_redir(t_command *cmd)
{
	int		prev_fd;
	t_elem	*cur_elem;
	t_redir	*cur_redir;

	prev_fd = -2;
	cur_elem = cmd->redir.head;
	while (cur_elem != NULL)
	{
		cur_redir = cur_elem->data;
		if (redir_one(cmd, cur_redir, &prev_fd) != 0)
			return (-1);
		cur_elem = cur_elem->next;
	}
	return (0);
}

void	exec_cmd(t_command *cur_cmd, t_minishell *sh)
{
	if (exec_redir(cur_cmd) != 0)
		perror_exit(NULL, sh);
	minishell_exit(sh, 0);
}
