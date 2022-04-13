/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 12:00:19 by ddordain          #+#    #+#             */
/*   Updated: 2022/04/13 15:14:33 by pwu              ###   ########.fr       */
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
		if (cur_cmd->pipefd[PIPE_RD] != -1)
			ft_close(&cur_cmd->pipefd[PIPE_RD]);
		if (cur_cmd->pipefd[PIPE_WR] != -1)
			ft_close(&cur_cmd->pipefd[PIPE_WR]);
		// if (cur_cmd->pid != -1)
		// 	kill(cur_cmd->pid, SIGTERM);
		cur_elem = cur_elem->next;
	}
	perror_exit(NULL, sh);
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
