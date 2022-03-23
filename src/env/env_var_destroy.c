/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_destroy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:29:53 by pwu               #+#    #+#             */
/*   Updated: 2022/03/23 13:32:24 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	env_var_destroy(void *data)
{
	t_env	*env_var;

	env_var = data;
	if (env_var != NULL)
	{
		if (env_var->name != NULL)
		{
			if (env_var->value != NULL)
				free(env_var->value);
			free(env_var->name);
		}
		free(env_var);
	}
}
