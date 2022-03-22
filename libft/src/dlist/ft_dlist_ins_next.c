/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_ins_next.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:49:53 by ddordain          #+#    #+#             */
/*   Updated: 2021/12/28 15:35:04 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/dlist.h"

static t_elem	*security_check(t_dlist *list, t_elem *element)
{
	t_elem	*new_element;

	if (element == NULL && ft_dlist_size(list) != 0)
		return (NULL);
	new_element = (t_elem *)malloc(sizeof(t_elem));
	if (new_element == NULL)
		return (NULL);
	else
		return (new_element);
}

int	ft_dlist_ins_next(t_dlist *list, t_elem *element, const void *data)
{
	t_elem	*new_element;

	new_element = security_check(list, element);
	if (new_element == NULL)
		return (-1);
	new_element->data = (void *)data;
	if (ft_dlist_size(list) == 0)
	{
		list->head = new_element;
		list->head->prev = NULL;
		list->head->next = NULL;
		list->tail = new_element;
	}
	else
	{
		new_element->next = element->next;
		new_element->prev = element;
		if (element->next == NULL)
			list->tail = new_element;
		else
			element->next->prev = new_element;
		element->next = new_element;
	}
	list->size++;
	return (0);
}
