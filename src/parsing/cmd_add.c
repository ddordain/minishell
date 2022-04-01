/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:36:11 by pwu               #+#    #+#             */
/*   Updated: 2022/04/01 13:48:15 by pwu              ###   ########.fr       */
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
		free(cmd);
	}
}

static int	cmd_error(t_command *cmd)
{
	cmd_destroy(cmd);
	return (-1);
}

static void	cmd_init(t_command *cmd)
{
	cmd->ac = 0;
	cmd->av = NULL;
	cmd->envp = NULL;
	ft_dlist_init(&cmd->redir, redir_destroy);
	cmd->fdin = -1;
	cmd->fdout = -1;
	cmd->pipein = -1;
	cmd->pipeout = -1;
}

int	cmd_add(t_dlist *tokens, t_dlist *commands)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (cmd_error(NULL));
	cmd_init(cmd);
	if (redir_add(cmd, tokens) != 0)
		return (cmd_error(cmd));
	if (av_add(cmd, tokens) != 0)
		return (cmd_error(cmd));
	if (ft_dlist_ins_next(commands, ft_dlist_tail(commands), cmd) != 0)
		return (cmd_error(cmd));
	return (0);
}
