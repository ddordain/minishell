/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:47:48 by ddordain          #+#    #+#             */
/*   Updated: 2021/11/23 11:47:48 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/mem.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*s_unchar;

	i = 0;
	s_unchar = (unsigned char *)s;
	while (i < n)
	{
		s_unchar[i] = '\0';
		++i;
	}
}
