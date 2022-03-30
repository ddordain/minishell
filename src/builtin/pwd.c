/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:34:48 by ddordain          #+#    #+#             */
/*   Updated: 2022/03/30 13:51:03 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*get_pwd(void)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (NULL);
	return (pwd);
}

void builtin_pwd(void)
{
	char*	str;

	str = get_pwd();
	if (str == NULL)
		return (perror("pwd"));
	ft_putstr_fd(str, 1);
	free(str);
}
