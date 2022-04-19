/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:00:38 by ddordain          #+#    #+#             */
/*   Updated: 2022/04/19 14:07:41 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    builtin_unset(t_command *cmd)
{
	t_elem	*elem;
	t_env	*data;
	int		i;

	i = 0;
	if (cmd->ac <= 1)
		return ;
	while (cmd->av[++i] != NULL)
	{
		elem = get_env_elem(&cmd->sh->dl_env, cmd->av[i]);
		if (elem != NULL)
		{
			data = ft_dlist_data(elem);
			ft_dlist_remove(&cmd->sh->dl_env, elem, (void *)&data);
			free(data);
		}
	}
}
