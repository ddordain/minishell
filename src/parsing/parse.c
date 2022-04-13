/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:17:09 by pwu               #+#    #+#             */
/*   Updated: 2022/04/13 15:59:57 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	parse(t_minishell *sh)
{
	t_elem	*cur_elem;
	t_tok	*cur_tok;

	cur_elem = sh->dl_tok.head;
	cur_tok = cur_elem->data;
	while (cur_tok->type != EOF_TOK)
	{
		var_expand(cur_tok, cur_elem->prev, sh);
		quote_remove(cur_tok, sh);
		cur_elem = cur_elem->next;
		cur_tok = cur_elem->data;
	}
}
