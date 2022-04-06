/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:06:07 by pwu               #+#    #+#             */
/*   Updated: 2022/04/06 18:29:01 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	redir_destroy(void *data)
{
	t_redir	*redir;

	redir = data;
	if (redir)
	{
		if (redir->var)
			free(redir->var);
		free(redir);
	}
}

// static int	redir_error(t_redir *redir)
// {
// 	redir_destroy(redir);
// 	return (-1);
// }

static int	redir_add_one(t_command *cmd, t_tok *cur_tok, t_tok *next_tok, t_minishell *sh)
{
	t_redir	*redir;

	redir = xmalloc(sizeof(t_redir), sh);
	if (ft_dlist_ins_next(&cmd->redir, ft_dlist_tail(&cmd->redir), redir) == -1)
		perror_exit("Malloc failure", sh);
	redir->var = ymalloc(ft_strlen(next_tok->content) + 1, sh);
	ft_memcpy(redir->var, next_tok->content, ft_strlen(next_tok->content));
	redir->var[ft_strlen(next_tok->content)] = 0;
	redir->type = cur_tok->type;
	return (0);
}

int	redir_add(t_command *cmd, t_dlist *tokens, t_minishell *sh)
{
	t_elem	*cur_elem;
	t_elem	*next_elem;
	t_tok	*cur_tok;
	t_tok	*next_tok;

	cur_elem = tokens->head;
	cur_tok = cur_elem->data;
	while (cur_tok->type != EOF_TOK && cur_tok->type != PIPE)
	{
		if (cur_tok->type >= REDIR_IN && cur_tok->type <= REDIR_APPEND)
		{
			if (redir_add_one(cmd, cur_tok, cur_elem->next->data, sh) != 0)
				return (-1);
			next_elem = cur_elem->next;
			next_tok = next_elem->data;
			cur_tok->type = NUL_TOK;
			next_tok->type = NUL_TOK;
			cur_elem = tokens->head;
		}
		else
			cur_elem = cur_elem->next;
		cur_tok = cur_elem->data;
	}
	return (0);
}
