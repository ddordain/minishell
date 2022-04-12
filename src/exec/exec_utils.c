/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:49:01 by pwu               #+#    #+#             */
/*   Updated: 2022/04/12 13:15:18 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_close(int *fd)
{
	if (*fd >= 3)
		if (close(*fd) == -1)
			return (perror("close()"), -1);
	*fd = -2;
	return (0);
}

void	exec_close_fds(t_elem *elem)
{
	t_command	*cur_cmd;
	t_command	*prev_cmd;

	cur_cmd = elem->data;
	if (elem->prev)
	{
		prev_cmd = elem->prev->data;
		ft_close(&prev_cmd->pipefd[PIPE_RD]);
	}
	ft_close(&cur_cmd->pipefd[PIPE_RD]);
	ft_close(&cur_cmd->pipefd[PIPE_WR]);
	ft_close(&cur_cmd->fdin);
	ft_close(&cur_cmd->fdout);
}

void	minishell_exit(t_minishell *sh, int status)
{
	ft_dlist_destroy(&sh->dl_tok);
	ft_dlist_destroy(&sh->dl_env);
	ft_dlist_destroy(&sh->dl_cmd);
	ft_dlist_destroy(&sh->dl_malloc);
	rl_clear_history();
	if (sh->cmdline.line != NULL)
		free(sh->cmdline.line);
	exit(status);
}
