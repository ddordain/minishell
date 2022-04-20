/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:04:29 by pwu               #+#    #+#             */
/*   Updated: 2022/04/20 14:54:53 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_cmd(t_elem *cur_elem, t_minishell *sh)
{
	t_command	*cur_cmd;
	int			err_code;

	cur_cmd = cur_elem->data;
	if (exec_redir(cur_elem, cur_cmd) != 0)
		minishell_exit(sh, 1, cur_cmd);
	if (exec_pipe(cur_elem, cur_cmd) != 0)
		minishell_exit(sh, 1, cur_cmd);
	if (cur_cmd->ac == 0)
		minishell_exit(sh, 0, cur_cmd);
	if (is_builtin(cur_cmd->av[0]) == true)
		err_code = launcher(cur_elem, cur_cmd);
	else
		err_code = exec_bin(cur_elem, cur_cmd);
	if (err_code != 0)
		minishell_exit(sh, err_code, cur_cmd);
	minishell_exit(sh, 0, cur_cmd);
}
