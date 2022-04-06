/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:22:57 by ddordain          #+#    #+#             */
/*   Updated: 2022/04/06 16:12:55 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	cd_return(int exit_status, char *error_msg)
{
	if (error_msg != NULL)
		write(2, error_msg, ft_strlen(error_msg));
	g_exit_status = exit_status;
}

void	builtin_cd(t_dlist *dl_env, t_command *cmd)
{
	char	*pwd;
	char	*old_pwd;
	char	*tmp;

	if (cmd->ac != 2)
		return (cd_return(1, "cd: invalid number of arguments\n"));
	if (access(cmd->av[0], F_OK | X_OK) == -1)
		return (perror("cd"));
	tmp = get_env_value(dl_env, "PWD");
	if (chdir(cmd->av[0]) == -1)
		return (perror("cd"));
	old_pwd = tmp;
	pwd = cmd->av[0];
	check_name(dl_env, "OLDPWD", cmd->sh);
	set_env_value(dl_env, "OLDPWD", old_pwd);
	set_env_value(dl_env, "PWD", pwd);
}
