/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:48:33 by pwu               #+#    #+#             */
/*   Updated: 2022/04/07 15:50:35 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_strdup_ymalloc(const char *s, t_minishell *sh)
{
	size_t	size;
	char	*dest;

	size = ft_strlen(s) + 1;
	dest = (char *)ymalloc(sizeof(char) * size, sh);
	if (dest == NULL)
		return (NULL);
	ft_memcpy(dest, s, size);
	return (dest);
}

char	*ft_itoa_ymalloc(t_minishell *sh, int n)
{
	char	*str;
	long	result;
	int		i;

	i = 1;
	str = (char *)ymalloc(sizeof(char) * (check_size(n) + 1), sh);
	if (str == NULL)
		return (NULL);
	if (n < 0)
		str[0] = '-';
	result = n;
	if (result < 0)
		result *= (-1);
	str[check_size(n)] = '\0';
	while (result >= 10)
	{
		str[check_size(n) - i] = (result % 10) + '0';
		result /= 10;
		i++;
	}
	str[check_size(n) - i] = (result % 10) + '0';
	return (str);
}

void	*xmalloc(size_t bytes, t_minishell *sh)
{
	void	*ptr;

	ptr = malloc(bytes);
	if (ptr == NULL)
		perror_exit("Malloc failure", sh);
	return (ptr);
}

void	*ymalloc(size_t bytes, t_minishell *sh)
{
	void	*ptr;

	ptr = malloc(bytes);
	if (ptr == NULL)
		perror_exit("Malloc failure", sh);
	if (ft_dlist_ins_next(&sh->dl_malloc, ft_dlist_tail(&sh->dl_malloc), ptr)
		!= 0)
	{
		free(ptr);
		perror_exit("Malloc failure", sh);
	}
	return (ptr);
}
