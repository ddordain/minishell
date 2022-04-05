/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:53:35 by ddordain          #+#    #+#             */
/*   Updated: 2022/04/05 14:34:42 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char *ft_strcat(char *dest, char *src)
{
	int i;
	int j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	return (dest);
}

static void	print_echo(bool n, int size, char **av, int ac)
{
	int		i;
	char	*buffer_line;

	i = 1;
	if (n == true)
		i = 2;
	buffer_line = ft_calloc(size, sizeof(char));
	if (buffer_line == NULL)
		return ;
	while (av[i] != NULL)
	{
		buffer_line = ft_strcat(buffer_line, av[i]);
		if (i < ac - 1)
			buffer_line = ft_strcat(buffer_line, " ");
		i++;
	}
	if (n == true)
		write(1, buffer_line, ft_strlen(buffer_line));
	else if (n == false)
	{
		write(1, buffer_line, ft_strlen(buffer_line));
		write(1, "\n", 1);
	}
	free(buffer_line);
}

void	builtin_echo(int ac, char **av)
{
	int		i;
	bool	n;
	int		size;

	i = 1;
	n = false;
	size = 0;
	if (ac <= 1)
	{
		printf("\n");
		return ;
	}
	if (strcmp(av[1], "-n") == 0)
	{
		i = 2;
		n = true;
	}
	while (av[i] != NULL)
	{
		size += ft_strlen(av[i]) + 1;
		i++;
	}
	print_echo(n, size, av, ac);
}