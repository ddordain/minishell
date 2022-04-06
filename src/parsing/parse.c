/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:17:09 by pwu               #+#    #+#             */
/*   Updated: 2022/04/06 17:10:03 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	parse(t_dlist *tokens, const t_dlist *env, t_minishell *sh)
{
	t_elem	*cur_elem;
	t_tok	*cur_tok;

	cur_elem = tokens->head;
	cur_tok = cur_elem->data;
	while (cur_tok->type != EOF_TOK)
	{
		if (var_expand(cur_tok, env, cur_elem->prev, sh) != 0)
			return (-1);
		check_heredoc(cur_tok, cur_elem->prev);
		if (quote_remove(cur_tok, sh) != 0)
			return (-1);
		cur_elem = cur_elem->next;
		cur_tok = cur_elem->data;
	}
	return (0);
}
