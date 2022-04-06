/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:36:11 by pwu               #+#    #+#             */
/*   Updated: 2022/04/06 18:28:10 by pwu              ###   ########.fr       */
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
		av_destroy(cmd->av);
		if (cmd->pipefd[0] != -1)
			close(cmd->pipefd[0]);
		if (cmd->pipefd[1] != -1)
			close(cmd->pipefd[1]);
		free(cmd);
	}
}

static int	cmd_error(t_command *cmd)
{
	cmd_destroy(cmd);
	return (-1);
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
	cmd->sh = sh;
}

int	cmd_add(t_dlist *tokens, t_dlist *commands, t_minishell *sh)
{
	t_command	*cmd;

	cmd = xmalloc(sizeof(t_command), sh);
	cmd_init(cmd, sh);
	if (ft_dlist_ins_next(commands, ft_dlist_tail(commands), cmd) != 0)
		perror_exit("Malloc failure", sh);
	if (redir_add(cmd, tokens, sh) != 0)
		return (cmd_error(cmd));
	if (av_add(cmd, tokens, sh) != 0)
		return (cmd_error(cmd));
	return (0);
}
