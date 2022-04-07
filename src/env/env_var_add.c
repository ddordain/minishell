/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:25:46 by pwu               #+#    #+#             */
/*   Updated: 2022/04/07 12:22:37 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*get_var_name(char *var, t_minishell *sh)
{
	int		i;
	char	*res;

	i = -1;
	while (var[++i] != '=')
		;
	res = ymalloc(sizeof(char) * (i + 1), sh);
	i = -1;
	while (var[++i] != '=')
		res[i] = var[i];
	res[i] = 0;
	return (res);
}

static char	*get_var_value(char *var, t_minishell *sh)
{
	int		i;
	char	*res;

	i = -1;
	res = ymalloc(sizeof(char) * (ft_strlen(var) + 1), sh);
	while (var[++i])
		res[i] = var[i];
	res[i] = 0;
	return (res);
}

int	env_var_add(t_minishell *sh, char *to_add)
{
	t_env	*env_var;

	env_var = xmalloc(sizeof(t_env), sh);
	if (ft_dlist_ins_next(
			&sh->dl_env, ft_dlist_tail(&sh->dl_env), env_var) == -1)
	{
		free(env_var);
		perror_exit("Malloc failure", sh);
	}
	env_var->name = get_var_name(to_add, sh);
	env_var->value = get_var_value(to_add + ft_strlen(env_var->name) + 1, sh);
	return (0);
}
