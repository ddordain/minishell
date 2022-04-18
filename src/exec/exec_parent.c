/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 13:32:56 by pwu               #+#    #+#             */
/*   Updated: 2022/04/18 18:45:44 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_in_parent(t_elem *elem, t_command *cmd)
{
	(void)cmd;
	(void)elem;
	if (exec_redir(elem, cmd) != 0)
		return (1);
	return (launcher(cmd));
}
