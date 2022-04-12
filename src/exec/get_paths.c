/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:01:20 by pwu               #+#    #+#             */
/*   Updated: 2022/04/12 14:17:51 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	str_tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

static void	destroy_paths(char **paths, const int upto)
{
	int	i;

	i = 0;
	while (i < upto)
	{
		if (paths[i] != NULL)
			free(paths[i]);
		i++;
	}
	free(paths);
}

static char	*add_slash(char *s1)
{
	char	*res;
	int		i;

	res = malloc(sizeof(char) * (ft_strlen(s1) + 2));
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
		paths[i] = add_slash(paths[i]);
		if (!paths[i])
			return (destroy_paths(paths, path_count), NULL);
	}
	return (paths);
}
