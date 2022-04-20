/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:22:57 by ddordain          #+#    #+#             */
/*   Updated: 2022/04/20 11:25:46 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	cd_return(int return_value, t_command *cmd, char *err_msg)
{
	if (cmd->pid == 0)
	{
		if (return_value == -1)
		{
			if (err_msg != NULL)
				write(2, err_msg, ft_len(err_msg));
			minishell_exit(cmd->sh, 1);
		}
		minishell_exit(cmd->sh, 0);
	}
	else
	{
		if (return_value == -1)
		{
			if (err_msg != NULL)
				write(2, err_msg, ft_len(err_msg));
			g_exit_status = 1;
		}
		else
			g_exit_status = 0;
	}
}

void	builtin_cd(t_minishell *sh, t_command *cmd)
{
	char	*pwd;
	char	*old_pwd;
	char	*tmp;

	if (cmd->ac != 2)
		return (cd_return(-1, cmd, "cd: invalid number of arguments\n"));
	if (access(cmd->av[1], F_OK | X_OK) == -1)
		return (perror("cd"), cd_return(-1, cmd, NULL));
	tmp = get_env_value(&sh->dl_env, "PWD");
	if (chdir(cmd->av[1]) == -1)
		return (perror("cd"), cd_return(-1, cmd, NULL));
	old_pwd = tmp;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		perror_exit("Malloc failure", sh);
	check_name("OLDPWD", sh);
	set_env_value(sh, "OLDPWD", old_pwd);
	set_env_value(sh, "PWD", pwd);
	free(pwd);
	cd_return(0, cmd, NULL);
}
