/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:55:31 by pwu               #+#    #+#             */
/*   Updated: 2022/04/19 13:54:16 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_len(const char *s)
{
	int	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	add_str(char *dst, const char *var, int *pos)
{
	int	i;

	i = -1;
	while (var && var[++i])
	{
		dst[*pos] = var[i];
		*pos = *pos + 1;
	}
}

int	quote_state(const char c, int quote)
{
	if (c == '\'')
	{
		if (quote == 0)
			quote = SQUOTE;
		else if (quote == SQUOTE)
			quote = 0;
	}
	if (c == '\"')
	{
		if (quote == 0)
			quote = DQUOTE;
		else if (quote == DQUOTE)
			quote = 0;
	}
	return (quote);
}

bool	is_quote(const char c, int *quote)
{
	int	quote_save;

	quote_save = *quote;
	if (c == '\'')
	{
		if (*quote == 0)
			*quote = SQUOTE;
		else if (*quote == SQUOTE)
			*quote = 0;
	}
	if (c == '\"')
	{
		if (*quote == 0)
			*quote = DQUOTE;
		else if (*quote == DQUOTE)
			*quote = 0;
	}
	if (quote_save == *quote)
		return (false);
	return (true);
}
