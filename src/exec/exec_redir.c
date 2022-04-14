/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 11:19:37 by pwu               #+#    #+#             */
/*   Updated: 2022/04/14 13:05:52 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	here_doc(t_redir *redir)
{
	char	*line;
	int		pipe_heredoc[2];

	if (pipe(pipe_heredoc) != 0)
		return (-1);
	// ctrl+c doit free line et fermer le pipe heredoc
	line = readline("> ");
	if (!line)
		return (0);
	while (line && ft_strcmp(line, redir->var))
	{
		write(pipe_heredoc[PIPE_WR], line, ft_len(line));
		write(pipe_heredoc[PIPE_WR], "\n", 1);
		free(line);
		line = readline("> ");
	}
	if (line)
		free(line);
	else
		write(2, "\n", 1);
	ft_close(&pipe_heredoc[PIPE_WR]);
	return (pipe_heredoc[PIPE_RD]);
}

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
	if (redir->type == REDIR_HEREDOC)
	{
		ft_close(&cmd->fdin);
		cmd->fdin = here_doc(redir);
	}
	if (redir->type == REDIR_APPEND)
	{
		ft_close(&cmd->fdout);
		cmd->fdout = open(redir->var, O_CREAT | O_WRONLY | O_APPEND);
	}
	if (cmd->fdin == -1 || cmd->fdout == -1)
		return (perror(redir->var), exec_close_fds(elem), -1);
	return (0);
}

int	exec_redir(t_elem *elem, t_command *cmd)
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
