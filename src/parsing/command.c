/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 16:27:56 by pwu               #+#    #+#             */
/*   Updated: 2022/04/01 13:56:03 by pwu              ###   ########.fr       */
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

int	make_cmds(t_dlist *tokens, t_dlist *commands)
{
	while (finish_parse(tokens) == false)
	{
		if (cmd_add(tokens, commands) != 0)
			return (-1);
	}
	return (0);
}
