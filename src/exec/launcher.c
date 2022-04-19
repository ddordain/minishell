/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 15:44:39 by ddordain          #+#    #+#             */
/*   Updated: 2022/04/19 14:09:23 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// static void	builtin_selector(t_command *cmd)
// {
// 	if (ft_strcmp(cmd->av[0], "cd") == 0)
// 	else if (ft_strcmp(cmd->av[0], "echo") == 0)
// 	else if (ft_strcmp(cmd->av[0], "env") == 0)
// 	else if (ft_strcmp(cmd->av[0], "exit") == 0)
// 	else if (ft_strcmp(cmd->av[0], "export") == 0)
// 	else if (ft_strcmp(cmd->av[0], "pwd") == 0)
// 	else if (ft_strcmp(cmd->av[0], "unset") == 0)
// }

int	write_fd(t_command *cmd, char *str)
{
	if (str == NULL)
		return (0);
	if (cmd->pid == 0)
		return (write(1, str, ft_len(str)));
	return (write(cmd->fdout, str, ft_len(str)));
}

int	launcher(t_command *cmd)
{
	if (ft_strcmp(cmd->av[0], "cd") == 0)
		builtin_cd(cmd->sh, cmd);
	else if (ft_strcmp(cmd->av[0], "echo") == 0)
		builtin_echo(cmd->sh, cmd);
	else if (ft_strcmp(cmd->av[0], "env") == 0)
		builtin_env(cmd);
	else if (ft_strcmp(cmd->av[0], "exit") == 0)
		builtin_exit(cmd);
	else if (ft_strcmp(cmd->av[0], "export") == 0)
		builtin_export(cmd->sh, cmd);
	else if (ft_strcmp(cmd->av[0], "pwd") == 0)
		builtin_pwd(cmd);
	else if (ft_strcmp(cmd->av[0], "unset") == 0)
		builtin_unset(cmd);
	return (g_exit_status);
}
