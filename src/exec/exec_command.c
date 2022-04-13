/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:04:29 by pwu               #+#    #+#             */
/*   Updated: 2022/04/13 11:27:32 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec_cmd(t_elem *cur_elem, t_minishell *sh)
{
	t_command	*cur_cmd;
	int			err_code;

	cur_cmd = cur_elem->data;
	if (exec_redir(cur_elem, cur_cmd) != 0)
		minishell_exit(sh, 1);
	if (exec_pipe(cur_elem, cur_cmd) != 0)
		minishell_exit(sh, 1);
	if (cur_cmd->ac == 0)
		minishell_exit(sh, 0);
	// is builtin ?
	err_code = exec_bin(cur_elem, cur_cmd);
	if (err_code != 0)
		minishell_exit(sh, err_code);
	minishell_exit(sh, 0);
}
