/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 14:53:33 by ddordain          #+#    #+#             */
/*   Updated: 2022/04/07 15:52:14 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NBR_H
# define NBR_H

# include <stddef.h>
# include <stdlib.h>

int		ft_atoi(const char *str);
char	*ft_itoa(int n);
int		check_size(int n);

#endif