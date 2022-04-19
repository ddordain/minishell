/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:34:48 by ddordain          #+#    #+#             */
/*   Updated: 2022/04/19 14:21:15 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
		return (perror("pwd"));
	write_fd(cmd, str);
	write_fd(cmd, "\n");
	free(str);
}
