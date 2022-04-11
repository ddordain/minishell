/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:49:01 by pwu               #+#    #+#             */
/*   Updated: 2022/04/11 13:25:01 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_close(int fd)
{
	if (fd >= 0)
		close(fd);
}

void	close_pipes(t_command *cmd)
{
	ft_close(cmd->pipefd[PIPE_RD]);
	ft_close(cmd->pipefd[PIPE_WR]);
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
