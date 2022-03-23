/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:36:58 by pwu               #+#    #+#             */
/*   Updated: 2022/03/23 13:43:20 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	set_env(t_dlist *env, char **envp)
{
	int		i;

	i = -1;
	ft_dlist_init(env, env_var_destroy);
	while (envp[++i])
		if (env_var_add(env, envp[i]) != 0)
			return (-1);
	return (0);
}
