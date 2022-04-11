/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:04:29 by pwu               #+#    #+#             */
/*   Updated: 2022/04/11 18:25:27 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	redir_one(t_elem *elem, t_command *cmd, t_redir *redir)
{
	if (redir->type == REDIR_IN)
	{
		ft_close(&cmd->fdin);
		cmd->fdin = open(redir->var, O_RDONLY);
	}
	if (redir->type == REDIR_TRUNC)
	{
		ft_close(&cmd->fdout);
		cmd->fdout = open(redir->var, O_CREAT | O_WRONLY | O_TRUNC);
	}
	// if (redir->type == REDIR_HEREDOC || redir->type == REDIR_HEREDOC_RAW)
		//heredoc function
	if (redir->type == REDIR_APPEND)
	{
		ft_close(&cmd->fdout);
		cmd->fdout = open(redir->var, O_CREAT | O_WRONLY | O_APPEND);
	}
	if (cmd->fdin == -1 || cmd->fdout == -1)
		return (perror(redir->var), exec_close_fds(elem), -1);
	return (0);
}

static int	exec_redir(t_elem *elem, t_command *cmd)
{
	t_elem	*cur_elem;
	t_redir	*cur_redir;

	cur_elem = cmd->redir.head;
	while (cur_elem != NULL)
	{
		cur_redir = cur_elem->data;
		if (redir_one(elem, cmd, cur_redir) != 0)
			return (-1);
		cur_elem = cur_elem->next;
	}
	return (0);
}

void	exec_cmd(t_elem *cur_elem, t_minishell *sh)
{
	t_command	*cur_cmd;

	cur_cmd = cur_elem->data;
	if (exec_redir(cur_elem, cur_cmd) != 0)
		minishell_exit(sh, 1, NULL);
	if (exec_pipe(cur_elem, cur_cmd) != 0)
		minishell_exit(sh, 1, NULL);
	minishell_exit(sh, 0, NULL);
}
