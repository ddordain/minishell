/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:48:33 by pwu               #+#    #+#             */
/*   Updated: 2022/04/06 17:41:56 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	*xmalloc(size_t bytes, t_minishell *sh)
{
	void	*ptr;

	ptr = malloc(bytes);
	if (ptr == NULL)
		perror_exit("Malloc failure", sh);
	return (ptr);
}

void	*ymalloc(size_t bytes, t_minishell *sh)
{
	void	*ptr;

	ptr = malloc(bytes);
	if (ptr == NULL)
		perror_exit("Malloc failure", sh);
	if (ft_dlist_ins_next(&sh->dl_malloc, ft_dlist_tail(&sh->dl_malloc), ptr)
		!= 0)
		perror_exit("Malloc failure", sh);
	return (ptr);
}
