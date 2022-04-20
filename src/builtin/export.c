/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 13:23:00 by ddordain          #+#    #+#             */
/*   Updated: 2022/04/20 14:55:01 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// return -1 if not valid, 0 if valid but no reset and 1 if valid and reset

static void	export_error(int *return_value, t_command *cmd, const char *arg)
{
	if (arg != NULL)
		write(2, "export: invalid argument(s)\n", 28);
	if (cmd->pid == 0)
		*return_value = 1;
	else
		g_exit_status = 1;
}

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

static void	export_and_set(t_minishell *sh, char *str)
{
	char	*name;
	char	*value;

	name = malloc_buffer_name(str, sh);
	value = malloc_buffer_value(str, sh);
	check_name(name, sh);
	set_env_value(sh, name, value);
}

static void	export_not_set(t_minishell *sh, char *str)
{
	char	*name;

	name = malloc_buffer_name(str, sh);
	check_name(name, sh);
}

void	builtin_export(t_minishell *sh, t_command *cmd)
{
	int	i;
	int	return_value;

	i = 0;
	return_value = 0;
	if (cmd->ac == 1)
	{
		write(2, "Export : invalid number of arguments (see man)\n", 47);
		if (cmd->pid == 0)
			minishell_exit(sh, 1, cmd);
		else
			g_exit_status = 1;
	}
	while (cmd->av[++i] != NULL)
	{
		if (is_valid_env_name(cmd->av[i]) == 1)
			export_and_set(sh, cmd->av[i]);
		else if (is_valid_env_name(cmd->av[i]) == 0)
			export_not_set(sh, cmd->av[i]);
		else if (is_valid_env_name(cmd->av[i]) == -1)
			export_error(&return_value, cmd, cmd->av[i]);
	}
	if (cmd->pid == 0)
		minishell_exit(sh, return_value, cmd);
}
