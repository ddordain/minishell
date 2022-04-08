/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:36:11 by pwu               #+#    #+#             */
/*   Updated: 2022/04/08 12:06:39 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	cmd_destroy(void *data)
{
	t_command	*cmd;

	cmd = data;
	if (cmd)
	{
		ft_dlist_destroy(&cmd->redir);
		free(cmd);
	}
}

static void	cmd_init(t_command *cmd, t_minishell *sh)
{
	cmd->ac = 0;
	cmd->av = NULL;
	cmd->envp = NULL;
	ft_dlist_init(&cmd->redir, free);
	cmd->fdin = -1;
	cmd->fdout = -1;
	cmd->pipefd[0] = -1;
	cmd->pipefd[1] = -1;
	cmd->pid = -1;
	cmd->sh = sh;
}

void	cmd_add(t_minishell *sh)
{
	t_command	*cmd;

	cmd = xmalloc(sizeof(t_command), sh);
	cmd_init(cmd, sh);
	if (ft_dlist_ins_next(&sh->dl_cmd, ft_dlist_tail(&sh->dl_cmd), cmd) != 0)
	{
		free(cmd);
		perror_exit("Malloc failure", sh);
	}
	redir_add(cmd, sh);
	av_add(cmd, sh);
}
