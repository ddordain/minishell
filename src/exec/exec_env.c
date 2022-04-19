/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:01:20 by pwu               #+#    #+#             */
/*   Updated: 2022/04/19 14:24:05 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*env_join(char *name, char *value)
{
	char	*res;
	int		i;
	int		j;

	res = malloc(sizeof(char) * (ft_len(name) + ft_len(value) + 2));
	if (!res)
		return (NULL);
	i = -1;
	while (name && name[++i])
		res[i] = name[i];
	res[i++] = '=';
	j = -1;
	while (value && value[++j])
		res[i++] = value[j];
	res[i] = 0;
	return (res);
}

char	**env_tab(t_dlist *dl_env)
{
	t_elem	*cur_elem;
	t_env	*cur_env;
	char	**envp;
	int		i;

	envp = malloc(sizeof(char *) * (dl_env->size + 1));
	if (!envp)
		return (NULL);
	cur_elem = dl_env->head;
	i = -1;
	while (cur_elem != NULL)
	{
		cur_env = cur_elem->data;
		envp[++i] = env_join(cur_env->name, cur_env->value);
		if (!envp[i])
			return (free_str_tab(envp, i), NULL);
		cur_elem = cur_elem->next;
	}
	envp[i + 1] = NULL;
	return (envp);
}	

char	*path_add_slash(char *s1)
{
	char	*res;
	int		i;

	if (!s1)
		return (NULL);
	res = malloc(sizeof(char) * (ft_len(s1) + 2));
	if (!res)
	{
		free(s1);
		return (NULL);
	}
	i = -1;
	while (s1[++i])
		res[i] = s1[i];
	res[i] = '/';
	res[i + 1] = 0;
	free(s1);
	return (res);
}

char	**get_paths(t_dlist *dl_env)
{
	char	**paths;
	char	*path_line;
	int		i;
	int		path_count;

	path_line = get_env_value(dl_env, "PATH");
	paths = ft_split(path_line, ':');
	if (!paths)
		return (NULL);
	i = -1;
	path_count = str_tab_len(paths);
	while (paths[++i] != NULL)
	{
		paths[i] = path_add_slash(paths[i]);
		if (!paths[i])
			return (free_str_tab(paths, path_count), NULL);
	}
	return (paths);
}
