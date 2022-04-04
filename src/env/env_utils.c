/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:09:44 by ddordain          #+#    #+#             */
/*   Updated: 2022/04/04 13:52:00 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	*get_env_data(t_dlist *dl_env, char *name)
{
	t_elem	*current_elem;
	t_env	*current_elem_data;
	char	*name_elem;

	if (ft_dlist_size(dl_env) == 0)
		return (NULL);
	current_elem = ft_dlist_head(dl_env);
	while (1)
	{
		current_elem_data = ft_dlist_data(current_elem);
		name_elem = current_elem_data->name;
		if (ft_strcmp(name_elem, name) == 0)
			return (current_elem_data);
		else if (ft_dlist_is_tail(current_elem) == true)
			break ;
		else
			current_elem = current_elem->next;
	}
	return (NULL);
}

t_elem	*get_env_elem(t_dlist *dl_env, char *name)
{
	t_elem	*current_elem;
	t_env	*current_elem_data;
	char	*name_elem;

	if (ft_dlist_size(dl_env) == 0)
		return (NULL);
	current_elem = ft_dlist_head(dl_env);
	while (1)
	{
		current_elem_data = ft_dlist_data(current_elem);
		name_elem = current_elem_data->name;
		if (ft_strcmp(name_elem, name) == 0)
			return (current_elem);
		else if (ft_dlist_is_tail(current_elem) == true)
			break ;
		else
			current_elem = current_elem->next;
	}
	return (NULL);
}

char	*get_env_value(t_dlist *dl_env, char *name)
{
	t_elem	*current_elem;
	t_env	*current_elem_data;
	char	*name_elem;

	if (ft_dlist_size(dl_env) == 0)
		return (NULL);
	current_elem = ft_dlist_head(dl_env);
	while (1)
	{
		current_elem_data = ft_dlist_data(current_elem);
		name_elem = current_elem_data->name;
		if (ft_strcmp(name_elem, name) == 0)
			return (current_elem_data->value);
		else if (ft_dlist_is_tail(current_elem) == true)
			break ;
		else
			current_elem = current_elem->next;
	}
	return (NULL);
}

int	set_env_value(t_dlist *dl_env, char *name, char *new_value)
{
	t_env	*address_env;
	char	*address_new_value;

	address_env = get_env_data(dl_env, name);
	address_new_value = ft_strdup(new_value);
	if (address_new_value == NULL)
		return (EXIT_FAILURE);
	if (address_env->value != NULL)	
		free(address_env->value);
	address_env->value = address_new_value;
	return (EXIT_SUCCESS);
}
