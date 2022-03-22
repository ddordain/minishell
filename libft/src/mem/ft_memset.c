/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:48:36 by ddordain          #+#    #+#             */
/*   Updated: 2021/11/23 11:48:36 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/mem.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s_uchar;

	i = 0;
	s_uchar = (unsigned char *)s;
	while (i < n)
	{
		s_uchar[i] = c;
		++i;
	}
	return (s_uchar);
}
