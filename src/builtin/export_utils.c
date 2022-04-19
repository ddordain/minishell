/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:08:23 by pwu               #+#    #+#             */
/*   Updated: 2022/04/19 15:12:17 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*malloc_buffer_value(char *str, t_minishell *sh)
{
	char	*buffer_value;
	int		start;
	int		buffer_size;

	buffer_size = 0;
	start = 0;
	while (str[start] != '\0' && str[start] != '=')
		start++;
	if (str[start] == '\0')
		return (NULL);
	start++;
	while (str[start + buffer_size] != '\0')
		buffer_size++;
	buffer_value = (char *)ymalloc(sizeof(char) * (buffer_size + 1), sh);
	buffer_value[buffer_size] = '\0';
	return (ft_memcpy(buffer_value, str + start, buffer_size));
}

char	*malloc_buffer_name(char *str, t_minishell *sh)
{
	char	*buffer_name;
	int		buffer_size;

	buffer_size = 0;
	while (str[buffer_size] != '\0' && str[buffer_size] != '=')
		buffer_size++;
	buffer_name = (char *)ymalloc(sizeof(char) * (buffer_size + 1), sh);
	buffer_name[buffer_size] = '\0';
	return (ft_memcpy(buffer_name, str, buffer_size));
}
