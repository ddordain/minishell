/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 14:01:03 by ddordain          #+#    #+#             */
/*   Updated: 2022/04/18 18:04:53 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	env_return(t_minishell *sh, int return_value, t_command *cmd)
{
	if (cmd->pid == 0)
	{
		if (return_value == -1)
			perror_exit("minishell", sh);
		minishell_exit(sh, 0);
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
		err = write_fd(cmd, cur_data->name);
		err = write_fd(cmd, "=");
		err = write_fd(cmd, cur_data->value);
		err = write_fd(cmd, "\n");
		if (err == -1)
			break ;
		cur_elem = cur_elem->next;
	}
	env_return(cmd->sh, err, cmd);
}
