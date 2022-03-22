/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:48:27 by ddordain          #+#    #+#             */
/*   Updated: 2021/11/28 13:56:17 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/mem.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	void	*find;

	i = 0;
	find = NULL;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
		{
			find = (unsigned char *)s + i;
			return (find);
		}
		++i;
	}
	return (NULL);
}
