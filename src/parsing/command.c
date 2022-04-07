/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 16:27:56 by pwu               #+#    #+#             */
/*   Updated: 2022/04/07 14:09:38 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	finish_parse(t_dlist *tokens)
{
	t_elem	*cur_elem;
	t_tok	*cur_tok;

	cur_elem = tokens->head;
	cur_tok = cur_elem->data;
	while (cur_tok->type != EOF_TOK)
	{
		if (cur_tok->type == PIPE)
		{
			cur_tok->type = NUL_TOK;
			return (false);
		}
		else if (cur_tok->type != NUL_TOK)
			return (false);
		cur_elem = cur_elem->next;
		cur_tok = cur_elem->data;
	}
	return (true);
}

void	make_cmds(t_minishell *sh)
{
	while (finish_parse(&sh->dl_tok) == false)
		cmd_add(sh);
}
