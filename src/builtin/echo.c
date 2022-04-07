/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:53:35 by ddordain          #+#    #+#             */
/*   Updated: 2022/04/07 16:17:00 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

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

static void	print_echo(bool n, int size, t_command *cmd, t_minishell *sh)
{
	int		i;
	char	*buffer_line;

	i = 1;
	if (n == true)
		i = 2;
	buffer_line = ymalloc(size * sizeof(char), sh);
	ft_bzero(buffer_line, size);
	while (cmd->av[i] != NULL)
	{
		buffer_line = ft_strcat(buffer_line, cmd->av[i]);
		if (i < cmd->ac - 1)
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
}

void	builtin_echo(t_minishell *sh, t_command *cmd)
{
	int		i;
	bool	n;
	int		size;

	i = 1;
	n = false;
	size = 0;
	if (cmd->ac <= 1)
	{
		printf("\n");
		return ;
	}
	if (strcmp(cmd->av[1], "-n") == 0)
	{
		i = 2;
		n = true;
	}
	while (cmd->av[i] != NULL)
	{
		size += ft_strlen(cmd->av[i]) + 1;
		i++;
	}
	print_echo(n, size, cmd, sh);
}
