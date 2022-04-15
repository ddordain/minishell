/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 12:46:17 by pwu               #+#    #+#             */
/*   Updated: 2022/04/15 16:36:33 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	here_doc(t_redir *redir)
{
	char	*line;
	int		pipe_heredoc[2];

	if (pipe(pipe_heredoc) != 0)
		return (perror("minishell"), -1);
	// ici ctrl+c doit free line, fermer le pipe heredoc et quitter le process
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
	// ici ctrl+c doit etre ignoré
	if (line)
		free(line);
	else
		write(2, "\n", 1);
	ft_close(&pipe_heredoc[PIPE_WR]);
	return (pipe_heredoc[PIPE_RD]);
}

static int	heredoc_one(t_command *cmd)
{
	t_elem	*cur_elem;
	t_redir	*cur_redir;

	cur_elem = cmd->redir.head;
	while (cur_elem != NULL)
	{
		cur_redir = cur_elem->data;
		if (cur_redir->type == REDIR_HEREDOC)
		{
			ft_close(&cmd->here_doc);
			cmd->here_doc = here_doc(cur_redir);
			if (cmd->here_doc == -1)
				return (-1);
		}
		cur_elem = cur_elem->next;
	}
	return (0);
}

static void	heredoc_error(t_elem *elem)
{
	t_command	*cmd;

	while (elem != NULL)
	{
		cmd = elem->data;
		ft_close(&cmd->here_doc);
		elem = elem->prev;
	}
}

int	make_heredocs(t_minishell *sh)
{
	t_elem		*cur_elem;
	t_command	*cur_cmd;

	cur_elem = sh->dl_cmd.head;
	while (cur_elem != NULL)
	{
		cur_cmd = cur_elem->data;
		heredoc_one(cur_cmd);
		if (cur_cmd->here_doc == -1)
			return (heredoc_error(cur_elem), 1);
		cur_elem = cur_elem->next;
	}
	return (0);
}
