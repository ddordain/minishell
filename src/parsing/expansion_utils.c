/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:55:31 by pwu               #+#    #+#             */
/*   Updated: 2022/03/25 14:57:39 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_len(const char *s)
{
	int	len;

	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

void	add_str(char *dst, const char *var, int *pos)
{
	int	i;

	i = -1;
	while (var[++i])
	{
		dst[*pos] = var[i];
		*pos = *pos + 1;
	}
}
