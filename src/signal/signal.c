/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:30:37 by ddordain          #+#    #+#             */
/*   Updated: 2022/04/12 15:43:59 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handler_rl(int signo, siginfo_t *si, void *ignore)
{
	(void) ignore;
	(void) si;
	if (signo == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("\n");
		rl_redisplay();
	}
}

void	handler_child(int signo, siginfo_t *si, void *ignore)
{
	(void) ignore;
	(void) si;
	if (signo == SIGINT)
		exit(2);
}

void	handler_parent(int signo, siginfo_t *si, void *ignore)
{
	(void) ignore;
	(void) si;
	if (signo == SIGINT)
		exit(2);
}

void	signal_handler(int handler, t_minishell *sh)
{
	struct sigaction	sa;

	sa = sh->sa;
	sigemptyset(&sa.sa_mask);
	if (handler == 0)
		sa.sa_handler = SIG_IGN;
	else if (handler == 1)
		sa.sa_sigaction = handler_rl;
	else if (handler == 2)
		sa.sa_sigaction = handler_parent;
	else if (handler == 3)
		sa.sa_sigaction = handler_child;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}