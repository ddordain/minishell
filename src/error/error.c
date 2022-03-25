/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 12:00:19 by ddordain          #+#    #+#             */
/*   Updated: 2022/03/25 15:01:59 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	perror_exit(const char *str, t_minishell *sh)
{
	if (str == NULL)
		perror("minishell");
	else
		perror(str);
	ft_dlist_destroy(&sh->dl_cmd);
	ft_dlist_destroy(&sh->dl_env);
	ft_dlist_destroy(&sh->dl_cmd);
	rl_clear_history();
	exit(EXIT_FAILURE);
}
