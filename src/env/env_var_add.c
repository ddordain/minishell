/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:25:46 by pwu               #+#    #+#             */
/*   Updated: 2022/03/23 13:34:20 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*get_var_name(char *var)
{
	int		i;
	char	*res;

	i = -1;
	while (var[++i] != '=')
		;
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	i = -1;
	while (var[++i] != '=')
		res[i] = var[i];
	res[i] = 0;
	return (res);
}

static char	*get_var_value(char *var)
{
	int		i;
	char	*res;

	i = -1;
	res = malloc(sizeof(char) * (ft_strlen(var) + 1));
	if (!res)
		return (NULL);
	while (var[++i])
		res[i] = var[i];
	res[i] = 0;
	return (res);
}

static int	alloc_error(t_env *env_var)
{
	env_var_destroy(env_var);
	perror("minishell");
	return (-1);
}

int	env_var_add(t_dlist *env, char *to_add)
{
	t_env	*env_var;

	env_var = malloc(sizeof(t_env));
	if (!env_var)
		return (alloc_error(NULL));
	env_var->name = get_var_name(to_add);
	if (!env_var->name)
		return (alloc_error(env_var));
	env_var->value = get_var_value(to_add + ft_strlen(env_var->name) + 1);
	if (!env_var->value)
		return (alloc_error(env_var));
	if (ft_dlist_ins_next(env, ft_dlist_tail(env), env_var) == -1)
		return (alloc_error(env_var));
	return (0);
}
