/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:37:42 by pwu               #+#    #+#             */
/*   Updated: 2022/03/18 16:38:02 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	quote_check(const char *line)
{
	int	i;
	int	quote_state;

	i = -1;
	quote_state = 0;
	while (line[++i])
	{
		if (line[i] == '\'')
		{
			if (quote_state == 0)
				quote_state = SQUOTE;
			else if (quote_state == SQUOTE)
				quote_state = 0;
		}
		if (line[i] == '"')
		{
			if (quote_state == 0)
				quote_state = DQUOTE;
			else if (quote_state == DQUOTE)
				quote_state = 0;
		}
	}
	return (quote_state);
}
