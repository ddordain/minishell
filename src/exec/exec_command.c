/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:04:29 by pwu               #+#    #+#             */
/*   Updated: 2022/04/12 14:22:22 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	exec_bin(t_elem *elem, t_command *cmd)
{
	char	**paths;

	paths = get_paths(&cmd->sh->dl_env);
	if (!paths && get_env_value(&cmd->sh->dl_env, "PATH") != NULL)
		return (exec_close_fds(elem), 1);

	return (0);
}

void	exec_cmd(t_elem *cur_elem, t_minishell *sh)
{
	t_command	*cur_cmd;
	int			err_code;

	cur_cmd = cur_elem->data;
	if (exec_redir(cur_elem, cur_cmd) != 0)
		minishell_exit(sh, 1);
	if (exec_pipe(cur_elem, cur_cmd) != 0)
		minishell_exit(sh, 1);
	// is builtin ?
	err_code = exec_bin(cur_elem, cur_cmd);
	if (err_code != 0)
		minishell_exit(sh, err_code);
	minishell_exit(sh, 0);
}
