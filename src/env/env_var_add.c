/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:25:46 by pwu               #+#    #+#             */
/*   Updated: 2022/04/06 18:05:48 by pwu              ###   ########.fr       */
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

// static int	alloc_error(t_env *env_var)
// {
// 	env_var_destroy(env_var);
// 	perror("minishell");
// 	return (-1);
// }

int	env_var_add(t_dlist *env, char *to_add, t_minishell *sh)
{
	t_env	*env_var;

	env_var = xmalloc(sizeof(t_env), sh);
	if (ft_dlist_ins_next(env, ft_dlist_tail(env), env_var) == -1)
	{
		free(env_var);
		perror_exit("Malloc failure", sh);
	}
	env_var->name = get_var_name(to_add, sh);
	env_var->value = get_var_value(to_add + ft_strlen(env_var->name) + 1, sh);
	return (0);
}
