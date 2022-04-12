/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 16:51:08 by pwu               #+#    #+#             */
/*   Updated: 2022/04/12 19:20:53 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	exec_error(char **paths, char **envp, t_elem *elem, int err_code)
{
	if (err_code == -1)
		perror("minishell");
	if (paths != NULL)
		free_str_tab(paths, str_tab_len(paths));
	if (envp != NULL)
		free_str_tab(envp, str_tab_len(envp));
	exec_close_fds(elem);
}

static void	prep_exec(t_command *cmd, char *to_exec)
{
	signal(SIGQUIT, SIG_DFL);
	execve(to_exec, cmd->av, cmd->envp);
}

int	exec_absolute(t_command *cmd)
{
	char	*to_exec;
	char	*tmp;

	tmp = path_add_slash(getcwd(NULL, 0));
	to_exec = ft_strjoin(tmp, cmd->av[0]);
	free(tmp);
	if (!to_exec)
		return (-1);
	if (access(to_exec, F_OK) == -1)
	{
		write(2, cmd->av[0], ft_len(cmd->av[0]));
		write(2, ": command not found\n", 20);
		return (free(to_exec), 127);
	}
	prep_exec(cmd, to_exec);
	return (free(to_exec), -1);
}

int	exec_bin(t_elem *elem, t_command *cmd)
{
	char	**paths;
	char	*to_exec;
	int		i;

	paths = get_paths(&cmd->sh->dl_env);
	if (!paths && get_env_value(&cmd->sh->dl_env, "PATH") != NULL)
		return (exec_error(NULL, NULL, elem, -1), 1);
	cmd->envp = env_tab(&cmd->sh->dl_env);
	if (!cmd->envp)
		return (exec_error(paths, NULL, elem, -1), 1);
	i = -1;
	while (paths != NULL && paths[++i])
	{
		to_exec = ft_strjoin(paths[i], cmd->av[0]);
		if (!to_exec)
			return (exec_error(paths, cmd->envp, elem, -1), 1);
		if (access(to_exec, F_OK | X_OK) != -1)
			prep_exec(cmd, to_exec);
		free(to_exec);
	}
	if (exec_absolute(cmd) == -1)
		return (exec_error(paths, cmd->envp, elem, -1), 1);
	return (exec_error(paths, cmd->envp, elem, 127), 127);
}
