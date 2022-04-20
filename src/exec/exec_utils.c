/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:49:01 by pwu               #+#    #+#             */
/*   Updated: 2022/04/20 14:52:16 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_close(int *fd)
{
	if (!fd)
		return (0);
	if (*fd >= 3)
		if (close(*fd) == -1)
			return (perror("close()"), -1);
	*fd = -2;
	return (0);
}

int	str_tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	free_str_tab(char **tab, const int upto)
{
	int	i;

	i = 0;
	while (i < upto)
	{
		if (tab[i] != NULL)
			free(tab[i]);
		i++;
	}
	free(tab);
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
	ft_close(&cur_cmd->here_doc);
}

void	minishell_exit(t_minishell *sh, int status, t_command *cmd)
{
	close(0);
	close(1);
	ft_close(&cmd->pipefd[PIPE_RD]);
	ft_dlist_destroy(&sh->dl_tok);
	ft_dlist_destroy(&sh->dl_env);
	ft_dlist_destroy(&sh->dl_cmd);
	ft_dlist_destroy(&sh->dl_malloc);
	rl_clear_history();
	if (sh->cmdline.line != NULL)
		free(sh->cmdline.line);
	exit(status);
}
