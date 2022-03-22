/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:48:56 by ddordain          #+#    #+#             */
/*   Updated: 2021/11/23 11:48:56 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strnlen(const char *s, size_t maxlen)
{
	size_t	i;

	i = 0;
	while (i < maxlen)
	{
		if (s[i] == '\0')
			break ;
		i++;
	}
	return (i);
}

size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	size_t	index_src;
	size_t	len_dest;
	size_t	len_src;

	len_dest = ft_strnlen(dest, destsize);
	len_src = ft_strlen((char *)src);
	if (destsize <= len_dest)
		return (destsize + len_src);
	index_src = 0;
	while (src[index_src] != '\0' && destsize > (len_dest + 1))
	{
		dest[len_dest] = src[index_src];
		index_src++;
		len_dest++;
	}
	dest[len_dest] = '\0';
	return (len_dest + ft_strlen((char *)(&src[index_src])));
}
