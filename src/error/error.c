/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 12:00:19 by ddordain          #+#    #+#             */
/*   Updated: 2022/04/07 13:18:41 by pwu              ###   ########.fr       */
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
	if (sh->cmdline.line != NULL)
		free(sh->cmdline.line);
	exit(EXIT_FAILURE);
}
