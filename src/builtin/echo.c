/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:53:35 by ddordain          #+#    #+#             */
/*   Updated: 2022/04/20 14:54:52 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	echo_return(t_minishell *sh, int return_value, t_command *cmd)
{
	if (cmd->pid == 0)
	{
		if (return_value == -1)
		{
			perror("minishell");
			minishell_exit(sh, 1, cmd);
		}
		minishell_exit(sh, 0, cmd);
	}
	else
	{
		if (return_value == -1)
		{
			perror("minishell");
			g_exit_status = 1;
		}
		else
			g_exit_status = 0;
	}
}

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

static void	print_echo(int n, int size, t_command *cmd, t_minishell *sh)
{
	int		i;
	char	*buffer_line;
	int		err_write;

	i = n + 1;
	buffer_line = ymalloc(size * sizeof(char), sh);
	ft_bzero(buffer_line, size);
	while (cmd->av[i] != NULL)
	{
		buffer_line = ft_strcat(buffer_line, cmd->av[i]);
		if (i < cmd->ac - 1)
			buffer_line = ft_strcat(buffer_line, " ");
		i++;
	}
	err_write = write_fd(cmd, buffer_line);
	if (n == 0)
		err_write = write_fd(cmd, "\n");
	echo_return(sh, err_write, cmd);
}

void	builtin_echo(t_minishell *sh, t_command *cmd)
{
	int		i;
	int		n;
	int		size;

	i = 1;
	n = 0;
	size = 0;
	while (cmd->av[i] && ft_strcmp(cmd->av[i], "-n") == 0)
	{
		i++;
		n++;
	}
	if (cmd->av[i] == NULL)
	{
		if (n == 0)
			echo_return(sh, write_fd(cmd, "\n"), cmd);
		return (echo_return(sh, write_fd(cmd, ""), cmd));
	}
	while (cmd->av[i] != NULL)
	{
		size += ft_strlen(cmd->av[i]) + 1;
		i++;
	}
	print_echo(n, size, cmd, sh);
}
