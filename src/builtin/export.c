/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 13:23:00 by ddordain          #+#    #+#             */
/*   Updated: 2022/04/07 16:03:32 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// return -1 if not valid, 0 if valid but no reset and 1 if valid and reset

static int	is_valid_env_name(char *name)
{
	int	i;

	i = 0;
	if (name[0] == '\0' || ft_isdigit(name[0]) == true)
		return (-1);
	while (name[i] != '\0' && name[i] != '=')
	{
		if (ft_isalnum(name[i]) || name[i] == '_')
			i++;
		else
			return (-1);
	}
	if (name[i] == '\0')
		return (0);
	else
		return (1);
}

static char *malloc_buffer_value(char *str, t_minishell *sh)
{
	char	*buffer_value;
	int		start;
	int		buffer_size;

	buffer_size = 0;
	start = 0;
	while(str[start] != '\0' && str[start] != '=')
		start++;
	if (str[start] == '\0')
		return (NULL);
	start++;
	while (str[start + buffer_size] != '\0')
		buffer_size++;
	buffer_value = (char *)ymalloc(sizeof(char) * (buffer_size + 1), sh);
	return (ft_memcpy(buffer_value, str + start, buffer_size));
}

static char	*malloc_buffer_name(char *str, t_minishell *sh)
{
	char	*buffer_name;
	int		buffer_size;

	buffer_size = 0;
	while(str[buffer_size] != '\0' && str[buffer_size] != '=')
		buffer_size++;
	buffer_name = (char *)ymalloc(sizeof(char) * (buffer_size + 1), sh);
	return (ft_memcpy(buffer_name, str, buffer_size));
}

static void	export_and_set(t_minishell *sh, char *str)
{
	char	*name;
	char	*value;

	name = malloc_buffer_name(str, sh);
	value = malloc_buffer_value(str, sh);
	check_name(name, sh);
	set_env_value(sh, name, value);
	free(name);
	free(value);
}

static void export_not_set(t_minishell *sh, char *str)
{
	char	*name;

	name = malloc_buffer_name(str, sh);
	check_name(name, sh);
	free(name);
}

void	builtin_export(t_minishell *sh, t_command *cmd)
{
	int		i; 

	i = 0;
	if (cmd->ac == 1)
		return ;
	while (cmd->av[++i] != NULL)
	{
		if (is_valid_env_name(cmd->av[i]) == 1)
			export_and_set(sh, cmd->av[i]);
		else if (is_valid_env_name(cmd->av[i]) == 0)
			export_not_set(sh, cmd->av[i]);
	}
}
