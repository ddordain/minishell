/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:59:45 by pwu               #+#    #+#             */
/*   Updated: 2022/03/30 15:16:49 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	has_quotes(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			return (true);
		++i;
	}
	return (false);
}

void	check_heredoc(t_tok *cur_tok, t_elem *prev_elem)
{
	t_tok	*prev_tok;

	if (!prev_elem)
		return ;
	prev_tok = prev_elem->data;
	if (prev_tok->type != REDIR_HEREDOC)
		return ;
	if (has_quotes(cur_tok->content) == true)
		prev_tok->type = REDIR_HEREDOC_RAW;
}
