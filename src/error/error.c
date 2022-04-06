/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 12:00:19 by ddordain          #+#    #+#             */
/*   Updated: 2022/04/06 17:45:41 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	perror_exit(const char *str, t_minishell *sh)
{
	if (str == NULL)
		perror("minishell");
	else if (strcmp(str, "Malloc failure") == 0)
		write(2, "Malloc failure\n", ft_strlen("Malloc failure\n"));
	else
		perror(str);
	ft_dlist_destroy(&sh->dl_tok);
	ft_dlist_destroy(&sh->dl_env);
	ft_dlist_destroy(&sh->dl_cmd);
	ft_dlist_destroy(&sh->dl_malloc);
	rl_clear_history();
//	free(sh->cmdline.line);
	exit(EXIT_FAILURE);
}
