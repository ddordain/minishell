/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_remove.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:49:59 by ddordain          #+#    #+#             */
/*   Updated: 2021/12/28 15:21:27 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/dlist.h"

int	ft_dlist_remove(t_dlist *list, t_elem *element, void **data)
{
	if (element == NULL || ft_dlist_size(list) == 0)
		return (-1);
	*data = element->data;
	if (element == list->head)
	{
		list->head = element->next;
		if (list->head == NULL)
			list->tail = NULL;
		else
			element->next->prev = NULL;
	}
	else
	{
		element->prev->next = element->next;
		if (element->next == NULL)
			list->tail = element->prev;
		else
			element->next->prev = element->prev;
	}
	free(element);
	list->size--;
	return (0);
}
