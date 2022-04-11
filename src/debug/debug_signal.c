#include "inc/minishell.h"

void	handler_main(int signo, siginfo_t *si, void *ignore)
{
	return (SIG_IGN);
} 

void	handler_rl(int signo, siginfo_t *si, void *ignore)
{
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
	if (signo == SIGINT)
		exit(2);
}

void	handler_parent(int signo, siginfo_t *si, void *ignore)
{
	if (signo == SIGINT)
	{
		exit(2);
	}
}

int main(void)
{
	pid_t pid;
	struct sigaction sa;
	char *buffer;

	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = handler_rl;
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
	buffer = readline(PROMPT);
	sa.sa_sigaction = handler_main;
	sigaction(SIGINT, &sa, NULL);
	pid = fork();
	if (pid == 0)
	{
		while (1)
		{	
			sa.sa_sigaction = handler_child;
			sigaction(SIGINT, &sa, NULL);
			printf("child process : %d\n", pid);
			usleep(1000000);
		}
	}
	else 
	{
		while (1)
		{	
			printf("parent proccess : %d\n", pid);
			usleep(1000000);
			waitpid(pid, NULL, NULL);
			sa.sa_sigaction = handler_parent;
			sigaction(SIGINT, &sa, NULL);
		}
	}
}