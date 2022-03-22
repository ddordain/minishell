/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:48:44 by ddordain          #+#    #+#             */
/*   Updated: 2021/11/23 11:48:44 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_tab_size(const char *s, char c)
{
	size_t	counter;

	counter = 0;
	while (*s)
	{
		counter++;
		s++;
		while (*s != c && *s)
			s++;
		while (*s == c && *s)
			s++;
	}
	return (counter);
}

static int	fill_tab(char const *s, char c, char **tab)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (*s)
	{
		len = 0;
		while (*s != c && *s && ++s)
			len++;
		tab[i] = malloc(len + 1);
		if (!tab[i])
		{
			while (i > 0)
				free(tab[--i]);
			free(tab);
			tab = NULL;
			return (1);
		}
		ft_strlcpy(tab[i++], s - len, len + 1);
		while (*s == c && *s)
			s++;
	}
	tab[i] = NULL;
	return (0);
}

char	**ft_split(const char *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	while (*s == c && *s)
		s++;
	tab = (char **)malloc(sizeof(char *) * (get_tab_size(s, c) + 1));
	if (!tab)
		return (NULL);
	if (fill_tab(s, c, tab))
		return (NULL);
	return (tab);
}
