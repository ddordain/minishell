/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_is_head.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 09:42:42 by ddordain          #+#    #+#             */
/*   Updated: 2021/12/28 15:21:09 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/dlist.h"

int	ft_dlist_is_head(t_elem *element)
{
	if (element->prev == NULL)
		return (1);
	else
		return (0);
}
