/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:34:48 by ddordain          #+#    #+#             */
/*   Updated: 2022/04/20 14:55:00 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	pwd_return(int return_value, t_command *cmd)
{
	if (cmd->pid == 0)
		minishell_exit(cmd->sh, return_value, cmd);
	else
		g_exit_status = return_value;
}

static char	*get_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (NULL);
	return (pwd);
}

void	builtin_pwd(t_command *cmd)
{
	char	*str;

	str = get_pwd();
	if (str == NULL)
		return (perror("pwd"), pwd_return(1, cmd));
	if (write_fd(cmd, str) == -1)
		return (perror("pwd"), free(str), pwd_return(1, cmd));
	if (write_fd(cmd, "\n") == -1)
		return (perror("pwd"), free(str), pwd_return(1, cmd));
	free(str);
	pwd_return(0, cmd);
}
