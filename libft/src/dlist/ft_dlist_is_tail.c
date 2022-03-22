/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_is_tail.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 09:42:46 by ddordain          #+#    #+#             */
/*   Updated: 2021/12/28 15:21:14 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/dlist.h"

int	ft_dlist_is_tail(t_elem *element)
{
	if (element->next == NULL)
		return (1);
	else
		return (0);
}
