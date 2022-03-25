/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:00:52 by pwu               #+#    #+#             */
/*   Updated: 2022/03/25 15:06:16 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	minishell_read(t_line *cmdline)
{
	cmdline->line = readline(PROMPT);
	if (!cmdline->line)
		return ;
	cmdline->len = ft_strlen(cmdline->line);
	if (cmdline->len > 0)
		add_history(cmdline->line);
	cmdline->i = 0;
}

void	debug_print_tok(t_dlist *tokens)
{
	t_elem	*cur_elem;
	t_tok	*cur_data;

	cur_elem = tokens->head;
	printf("tokens: %d\n\n", tokens->size);
	while (cur_elem != NULL)
	{
		cur_data = cur_elem->data;
		printf("type: %d content: [%s]\n", cur_data->type, cur_data->content);
		cur_elem = cur_elem->next;
	}
}

int	minishell_start(t_line *cmdline, t_minishell *sh)
{
	if (lex(cmdline, &sh->dl_tok) != 0)
		return (-1);
	if (parse(&sh->dl_tok, &sh->dl_env) != 0)
		return (-1);
	debug_print_tok(&sh->dl_tok);
	ft_dlist_destroy(&sh->dl_tok);
	return (0);
}

void	debug_print_env(t_dlist *env_start)
{
	t_elem	*cur_elem;
	t_env	*cur_data;

	cur_elem = env_start->head;
	printf("environment variables: %d\n", env_start->size);
	while (cur_elem != NULL)
	{
		cur_data = cur_elem->data;
		printf("%s = %s\n", cur_data->name, cur_data->value);
		cur_elem = cur_elem->next;
	}
}

static void	minishell_init(t_minishell *sh)
{
	ft_dlist_init(&sh->dl_cmd, free);
	ft_dlist_init(&sh->dl_env, env_var_destroy);
	ft_dlist_init(&sh->dl_tok, tok_destroy);
}

int	main(int ac, char **av, char **envp)
{
	t_line		cmdline;
	t_minishell	sh;

	(void)ac;
	(void)av;
	minishell_init(&sh);
	if (set_env(&sh.dl_env, envp) != 0)
	{
		ft_dlist_destroy(&sh.dl_env);
		return (EXIT_FAILURE);
	}
	debug_print_env(&sh.dl_env);
	while (1)
	{
		minishell_read(&cmdline);
		if (!cmdline.line)
			break ;
		if (minishell_start(&cmdline, &sh) != 0)
			perror_exit(NULL, &sh);
		free(cmdline.line);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
