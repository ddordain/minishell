/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 14:01:03 by ddordain          #+#    #+#             */
/*   Updated: 2022/04/20 14:54:51 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	env_return(t_minishell *sh, int return_value, t_command *cmd)
{
	if (cmd->pid == 0)
	{
		if (return_value == -1)
		{
			perror("minishell");
			minishell_exit(sh, 1, cmd);
		}
		minishell_exit(sh, 0, cmd);
	}
	else
	{
		if (return_value == -1)
		{
			perror("minishell");
			g_exit_status = 1;
		}
		else
			g_exit_status = 0;
	}
}

void	builtin_env(t_command *cmd)
{
	t_elem	*cur_elem;
	t_env	*cur_data;
	int		err;

	cur_elem = cmd->sh->dl_env.head;
	while (cur_elem != NULL)
	{
		cur_data = cur_elem->data;
		if (cur_data->value != NULL)
		{
			err = write_fd(cmd, cur_data->name);
			err = write_fd(cmd, "=");
			err = write_fd(cmd, cur_data->value);
			err = write_fd(cmd, "\n");
		}
		if (err == -1)
			break ;
		cur_elem = cur_elem->next;
	}
	env_return(cmd->sh, err, cmd);
}
