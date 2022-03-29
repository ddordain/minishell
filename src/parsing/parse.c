/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:17:09 by pwu               #+#    #+#             */
/*   Updated: 2022/03/29 12:48:15 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// 1. expand
// 2. split
// 3. unquote
int	parse(t_dlist *tokens, const t_dlist *env)
{
	t_elem	*cur_elem;
	t_tok	*cur_tok;

	cur_elem = tokens->head;
	cur_tok = cur_elem->data;
	while (cur_tok->type != EOF_TOK)
	{
		if (var_expand(cur_tok, env) != 0)
			return (-1);
		if (quote_remove(cur_tok) != 0)
			return (-1);
		cur_elem = cur_elem->next;
		cur_tok = cur_elem->data;
	}
	return (0);
}
