/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:30:37 by ddordain          #+#    #+#             */
/*   Updated: 2022/04/13 11:25:58 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	handler_rl(int signo, siginfo_t *si, void *ignore)
{
	(void) ignore;
	(void) si;
	if (signo == SIGINT)
	{
		// printf("^C");
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("\n");
		rl_redisplay();
	}
	// if (signo == SIGQUIT)
		// return ;
}

static void	handler_child(int signo, siginfo_t *si, void *ignore)
{
	(void) ignore;
	(void) si;
	if (signo == SIGINT)
	{
		// printf("^C");
		exit(2);
	}
	// if (signo == SIGQUIT)
		// return ;
}

static void	handler_parent(int signo, siginfo_t *si, void *ignore)
{
	(void) ignore;
	(void) si;
	if (signo == SIGINT)
	{
		// printf("^C");
		exit(2); 
	}
	// if (signo == SIGQUIT)
		// return ;
}

// static void	echo_off(void)
// {
// 	struct termios	term;

// 	tcgetattr(STDIN_FILENO, &term);
// 	term.c_lflag &= ~ECHOCTL;
// 	tcsetattr(STDIN_FILENO, TCSANOW, &term);
// }

// void	echo_on(void)
// {
// 	struct termios	term;

// 	tcgetattr(STDIN_FILENO, &term);
// 	term.c_lflag |= ECHOCTL;
// 	tcsetattr(STDIN_FILENO, TCSANOW, &term);
// }

void	signal_handler(int handler, t_minishell *sh)
{
	struct sigaction	sa;

	sa = sh->sa;

	sigemptyset(&sa.sa_mask);
	if (handler == 0)
		sa.sa_handler = SIG_IGN;
	if (handler == 1)
		sa.sa_sigaction = handler_rl;
	else if (handler == 2)
		sa.sa_sigaction = handler_parent;
	else if (handler == 3)
		sa.sa_sigaction = handler_child;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
