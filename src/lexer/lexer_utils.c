/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 11:20:15 by pwu               #+#    #+#             */
/*   Updated: 2022/03/21 17:03:56 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_space(const char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

bool	is_operator(const char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (true);
	return (false);
}

bool	is_type(const int type, const char c, int *quote_state)
{
	if (type == WORD)
	{
		if (c == '\'')
		{
			if (*quote_state == 0)
				*quote_state = SQUOTE;
			else if (*quote_state == SQUOTE)
				*quote_state = 0;
		}
		if (c == '\"')
		{
			if (*quote_state == 0)
				*quote_state = DQUOTE;
			else if (*quote_state == DQUOTE)
				*quote_state = 0;
		}
		if (c && ((!is_operator(c) && !is_space(c)) || (*quote_state != 0)))
			return (true);
		return (false);
	}
	return (is_operator(c));
}

int	find_operator(const char *line, const int start)
{
	int	type;
	int	i;

	i = start;
	if (line[i] == '<')
		type = REDIR_IN;
	else if (line[i] == '>')
		type = REDIR_TRUNC;
	else if (line[i] == '|')
		type = PIPE;
	else
		type = INVAL_OP;
	++i;
	if (!is_operator(line[i]))
		return (type);
	else if (line[i] == '<' && type == REDIR_IN)
		type = REDIR_HEREDOC;
	else if (line[i] == '>' && type == REDIR_TRUNC)
		type = REDIR_APPEND;
	else
		type = INVAL_OP;
	++i;
	if (!is_operator(line[i]))
		return (type);
	return (INVAL_OP);
}
