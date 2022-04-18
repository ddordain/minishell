/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 14:11:14 by ddordain          #+#    #+#             */
/*   Updated: 2022/04/18 19:04:34 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static long long	ll_checker(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	result;

	i = 0;
	sign = 1;
	result = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		++i;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		++i;
	}
	if (result > 9223372036854775807LL && sign == 1)
		return (-1);
	if (result > 9223372036854775808ULL && sign == -1)
		return (-1);
	return (result * sign);
}

static void	exit_return(t_command *cmd, int return_value, char *err_msg)
{
	if (cmd->pid == 0)
	{
		if (return_value == 2)
			write_fd(cmd, err_msg);
		minishell_exit(cmd->sh, return_value);
	}
	else
	{
		if (return_value == 2)
			write_fd(cmd, err_msg);
		g_exit_status = return_value;
	}
}

static int	check_number(char *av)
{
	char	sign;
	int		size;

	size = ft_len(av);
	if (av == NULL || av[0] == 0)
		return (EXIT_FAILURE);
	sign = 0;
	while (*av)
	{
		if (*av == '+' || *av == '-')
			sign++;
		else if (!ft_isdigit(*av))
			return (EXIT_FAILURE);
		if (sign > 1 || (sign == 1 && size == 1))
			return (EXIT_FAILURE);
		av++;
	}
	return (EXIT_SUCCESS);
}


void	builtin_exit(t_command *cmd)
{
	write_fd(cmd, "exit\n");
	if (cmd->ac > 2)
		return (exit_return(cmd, 2, "exit: too many arguments\n"));
	if (cmd->ac == 1)
		minishell_exit(cmd->sh, g_exit_status);
	if ((ll_checker(cmd->av[1]) == -1 && ft_len(cmd->av[1]) > 2)
			|| check_number(cmd->av[1]) == EXIT_FAILURE)
		exit_return(cmd, 2, "exit: invalid argument\n");
	else
		g_exit_status = ll_checker(cmd->av[1]);
	minishell_exit(cmd->sh, g_exit_status);
}
