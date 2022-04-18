/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 12:46:17 by pwu               #+#    #+#             */
/*   Updated: 2022/04/18 18:04:14 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	heredoc_eof(t_redir *redir)
{
	write(2, "minishell: warning: here-document delimited \
by end-of-file (wanted `", 68);
	write(2, redir->var, ft_len(redir->var));
	write(2, "')\n", 3);
}

static int	here_doc(t_minishell *sh, t_redir *redir)
{
	t_heredoc	doc;

	(void) sh;
	if (pipe(doc.pipe_heredoc) != 0)
		return (perror("minishell"), -1);
	doc.line = readline("> ");
	if (!doc.line)
		return (heredoc_eof(redir), ft_close(&doc.pipe_heredoc[PIPE_WR]),
			doc.pipe_heredoc[PIPE_RD]);
	while (doc.line && ft_strcmp(doc.line, redir->var))
	{
		write(doc.pipe_heredoc[PIPE_WR], doc.line, ft_len(doc.line));
		write(doc.pipe_heredoc[PIPE_WR], "\n", 1);
		free(doc.line);
		doc.line = readline("> ");
	}
	if (doc.line)
		free(doc.line);
	else
		heredoc_eof(redir);
	ft_close(&doc.pipe_heredoc[PIPE_WR]);
	return (doc.pipe_heredoc[PIPE_RD]);
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
			cmd->here_doc = here_doc(cmd->sh, cur_redir);
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
