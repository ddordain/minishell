/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 12:01:22 by ddordain          #+#    #+#             */
/*   Updated: 2021/11/28 16:25:58 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_min_size(size_t a, size_t b)
{
	if (a <= b)
		return (a);
	else
		return (b);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	strsize;

	strsize = ft_strlen(s);
	if (start >= strsize)
		return (ft_calloc(1, 1));
	s = s + start;
	len = ft_min_size(len, ft_strlen(s));
	substr = ft_calloc(len + 1, sizeof(char));
	if (substr == NULL)
		return (NULL);
	return ((char *)ft_memcpy(substr, s, len));
}
