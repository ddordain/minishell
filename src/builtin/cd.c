/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:22:57 by ddordain          #+#    #+#             */
/*   Updated: 2022/03/28 17:29:54 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	builtin_cd(t_dlist *dl_env, char *path)
{
	char	*pwd;
	char	*old_pwd;
	char	*tmp;

	if (path == NULL)
		return ;
	if (access(path, F_OK | X_OK) == -1)
		return (perror("cd"));
	tmp = get_env_value(dl_env, "PWD");
	if (chdir(path) == -1)
		return (perror("cd"));
	old_pwd = tmp;
	pwd = path;
	set_env_value(dl_env, "OLDPWD", old_pwd);
	set_env_value(dl_env, "PWD", pwd);
}
