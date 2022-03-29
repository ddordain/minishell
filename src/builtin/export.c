/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 13:23:00 by ddordain          #+#    #+#             */
/*   Updated: 2022/03/29 18:15:36 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
static bool	is_valid_env_name(t_dlist *dl_env, char *name)
{
	int	i;

	i = 0;
	if (name[0] == '\0' || ft_isdigit(name[0]) == true)
		return (false);
	else
	{
		while (name[i] != '\0' || name[i] != '=')
		{
			if (ft_isalnum(name[i]) || name[i] == '_')
				i++;
			else
				return (false);
		}
	}
	return (true);
}
*/
int		check_name(t_dlist *dl_env, char *buffer_name)
{
	t_env	*data;
	char	*name;

	if (get_env_elem(dl_env, buffer_name) != NULL)
		return (EXIT_SUCCESS);
	data = (t_env *)malloc(sizeof(t_env));
	if (data == NULL)
		return (EXIT_FAILURE);
	name = ft_strdup(buffer_name);
	if (name == NULL)
		return (EXIT_FAILURE);
	data->name = name;
	if (ft_dlist_ins_next(dl_env, dl_env->tail, data) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		export_name(t_dlist *dl_env, char **av, int nb_name_to_set)
{
	char	*buffer_name;
	int		buffer_size;

	while(nb_name_to_set-- > 1)
	{
		buffer_size = 0;
		while(av[nb_name_to_set][buffer_size] != '\0'
			&& av[nb_name_to_set][buffer_size] != '=')
			buffer_size++;
		buffer_name = (char *)malloc(sizeof(char) * (buffer_size + 1));
		if (buffer_name == NULL)
			return (EXIT_FAILURE);
		ft_memcpy(buffer_name, av[nb_name_to_set], buffer_size);
		buffer_name[buffer_size] = '\0';
		if (check_name(dl_env, buffer_name) == EXIT_FAILURE)
		{
			free(buffer_name);
			return (EXIT_FAILURE);
		}
		free(buffer_name);
	}
	return (EXIT_SUCCESS);
}
/*
void	builtin_export(t_dlist *dl_env, int ac, char **av)
{
	int		i; 

	i = 0;
	if (ac == 1)
		return ();
	while (av[i] != NULL)
	{
		if(is_valid_env_name(dl_env, av[i]) == false)
			ft_putstr_fd("export : not a valid identifier\n", 2);
		i++;
	}
}
*/