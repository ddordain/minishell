/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:40:38 by ddordain          #+#    #+#             */
/*   Updated: 2021/12/28 15:22:44 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/list.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*previous;

	if (lst == NULL || del == NULL)
		return ;
	while (*lst != NULL)
	{
		del((*lst)->content);
		previous = *lst;
		*lst = (*lst)->next;
		free(previous);
	}
	*lst = NULL;
}
