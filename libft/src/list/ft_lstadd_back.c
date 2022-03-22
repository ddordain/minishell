/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:59:06 by ddordain          #+#    #+#             */
/*   Updated: 2021/12/28 15:22:31 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/list.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*last_element;

	if (alst == NULL || new == NULL)
		return ;
	if (*alst != NULL)
	{
		last_element = ft_lstlast(*alst);
		last_element->next = new;
	}
	else
		*alst = new;
}
