/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:00:38 by ddordain          #+#    #+#             */
/*   Updated: 2022/04/04 13:55:46 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    builtin_unset(t_dlist *dl_env, int ac, char **av)
{
	t_elem	*elem;
	t_env	*data;
	int		i;

	i = 0;
	if (ac <= 1)
		return ;
	while (av[++i] != NULL)
	{
		elem = get_env_elem(dl_env, av[i]);
		if (elem != NULL)
		{
			data = ft_dlist_data(elem);
			if (data->name != NULL)
				free(data->name);
			if (data->value != NULL)
				free(data->value);
			ft_dlist_remove(dl_env, elem, (void *)&data);
		}
	}
}