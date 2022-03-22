/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:48:25 by ddordain          #+#    #+#             */
/*   Updated: 2021/11/23 11:48:25 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/nbr.h"

int	check_size(int n)
{
	int		count;
	long	result;

	result = n;
	count = 1;
	if (result < 0)
	{
		count++;
		result *= (-1);
	}
	while (result >= 10)
	{
		count++;
		result /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	result;
	int		i;

	i = 1;
	str = (char *)malloc(sizeof(char) * check_size(n) + 1);
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
