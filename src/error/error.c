/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 12:00:19 by ddordain          #+#    #+#             */
/*   Updated: 2022/04/15 16:40:03 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	pre_exec_error(const char *s, t_minishell *sh)
{
	t_elem		*cur_elem;
	t_command	*cur_cmd;

	perror(s);
	cur_elem = sh->dl_cmd.head;
	while (cur_elem != NULL)
	{
		cur_cmd = cur_elem->data;
		ft_close(&cur_cmd->pipefd[PIPE_RD]);
		ft_close(&cur_cmd->pipefd[PIPE_WR]);
		ft_close(&cur_cmd->here_doc);
		if (cur_cmd->pid >= 0)
			kill(cur_cmd->pid, SIGTERM);
		cur_elem = cur_elem->next;
	}
	g_exit_status = 129;
}

void	perror_exit(const char *str, t_minishell *sh)
{
	if (str == NULL)
		;
	else if (ft_strcmp(str, "Malloc failure") == 0)
		write(2, "Malloc failure\n", ft_strlen("Malloc failure\n"));
	else
		perror(str);
	ft_dlist_destroy(&sh->dl_tok);
	ft_dlist_destroy(&sh->dl_env);
	ft_dlist_destroy(&sh->dl_cmd);
	ft_dlist_destroy(&sh->dl_malloc);
	rl_clear_history();
	if (sh->cmdline.line != NULL)
		free(sh->cmdline.line);
	exit(EXIT_FAILURE);
}
