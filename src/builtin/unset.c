/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:00:38 by ddordain          #+#    #+#             */
/*   Updated: 2022/04/19 18:21:15 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	unset_error(int *return_value, t_command *cmd, const char *arg)
{
	if (arg != NULL)
	{
		write(2, "unset: `", 8);
		write(2, arg, ft_len(arg));
		write(2, "': not a valid identifier\n", 26);
	}
	if (cmd->pid == 0)
		*return_value = 1;
	else
		g_exit_status = 1;
}

static int	is_valid_env_name(char *name)
{
	int	i;

	i = 0;
	if (name[0] == '\0' || ft_isdigit(name[0]) == true)
		return (-1);
	while (name[i] != '\0' && name[i] != '=')
	{
		if (ft_isalnum(name[i]) || name[i] == '_')
			i++;
		else
			return (-1);
	}
	if (name[i] == '\0')
		return (0);
	else
		return (1);
}

void	builtin_unset(t_command *cmd)
{
	t_elem	*elem;
	t_env	*data;
	int		i;
	int		return_value;

	i = 0;
	return_value = 0;
	while (cmd->ac > 1 && cmd->av[++i] != NULL)
	{
		if (is_valid_env_name(cmd->av[i]) == -1)
			unset_error(&return_value, cmd, cmd->av[i]);
		elem = get_env_elem(&cmd->sh->dl_env, cmd->av[i]);
		if (elem != NULL)
		{
			data = ft_dlist_data(elem);
			ft_dlist_remove(&cmd->sh->dl_env, elem, (void *)&data);
			free(data);
		}
	}
	if (cmd->pid == 0)
		minishell_exit(cmd->sh, return_value);
	g_exit_status = return_value;
}
