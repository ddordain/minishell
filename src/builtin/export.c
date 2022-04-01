/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 13:23:00 by ddordain          #+#    #+#             */
/*   Updated: 2022/03/30 16:18:20 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


static bool	is_valid_env_name(char *name)
{
	int	i;

	i = 0;
	if (name[0] == '\0' || ft_isdigit(name[0]) == true)
		return (false);
	else
	{
		while (name[i] != '\0' && name[i] != '=')
		{
			if (ft_isalnum(name[i]) || name[i] == '_')
				i++;
			else
				return (false);
		}
	}
	return (true);
}

static int	check_name(t_dlist *dl_env, char *buffer_name)
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

static char *malloc_buffer_value(char *str)
{
	char	*buffer_value;
	int		start;
	int		buffer_size;

	buffer_size = 0;
	start = 0;
	while(str[start] != '\0' && str[start] != '=')
		start++;
	if (str[start] == '\0')
		return (NULL);
	start++;
	while (str[start + buffer_size] != '\0')
		buffer_size++;
	buffer_value = (char *)ft_calloc(sizeof(char),buffer_size + 1);
	if (buffer_value == NULL)
		return (NULL);
	return (ft_memcpy(buffer_value, str + start, buffer_size));
}

static char	*malloc_buffer_name(char *str)
{
	char	*buffer_name;
	int		buffer_size;

	buffer_size = 0;
	while(str[buffer_size] != '\0' && str[buffer_size] != '=')
		buffer_size++;
	buffer_name = (char *)ft_calloc(sizeof(char), buffer_size + 1);
	if (buffer_name == NULL)
		return (NULL);
	return (ft_memcpy(buffer_name, str, buffer_size));
}

void	builtin_export(t_dlist *dl_env, int ac, char **av)
{
	int		i; 
	char	*name;
	char	*value;

	i = 1;
	if (ac == 1)
		return ;
	while (av[i] != NULL)
	{
		if (is_valid_env_name(av[i]) == true)
		{
			name = malloc_buffer_name(av[i]);
			if (check_name(dl_env, name) == EXIT_FAILURE)
				perror("export");
			value = malloc_buffer_value(av[i]);
			set_env_value(dl_env, name, value);
			free(name);
			free(value);
		}
		i++;
	}
}

/*
static int	export_name(t_dlist *dl_env, char *str)
{
	char	*buffer_name;
	int		buffer_size;

	
	buffer_size = 0;
	while(str[buffer_size] != '\0' && str[buffer_size] != '=')
		buffer_size++;
	buffer_name = (char *)ft_calloc(sizeof(char), buffer_size + 1);
	if (buffer_name == NULL)
		return (EXIT_FAILURE);
	ft_memcpy(buffer_name, str, buffer_size);
	if (check_name(dl_env, buffer_name) == EXIT_FAILURE)
	{
		free(buffer_name);
		return (EXIT_FAILURE);
	}
	free(buffer_name);
	return (EXIT_SUCCESS);
}

static int	export_value(t_dlist *dl_env, char *str)
{
	char	*buffer_value;
	int		start;
	int		buffer_size;
	t_env	*elem;

	buffer_size = 0;
	start = 0;
	while(str[start] != '\0' && str[start] != '=')
		start++;
	if (str[start] == '\0')
		return (EXIT_FAILURE);
	start++;
	while (str[start + buffer_size] != '\0')
		buffer_size++;
	buffer_value = (char *)ft_calloc(sizeof(char),buffer_size + 1);
	if (buffer_value == NULL)
		return (EXIT_FAILURE);
	ft_memcpy(buffer_value, str + start, buffer_size);
	elem = get_env_elem(dl_env, );
	if (set_env_value(dl_env, elem->name, buffer_value) == EXIT_FAILURE)
	{
		free(buffer_value);
		return (EXIT_FAILURE);
	}
	printf("end of export value, name : %s value : %s\n", elem->name, elem->value);
	free(buffer_value);
	return (EXIT_SUCCESS);
}
*/