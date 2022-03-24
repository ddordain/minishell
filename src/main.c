/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:00:52 by pwu               #+#    #+#             */
/*   Updated: 2022/03/24 17:52:06 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	read_line(t_line *cmdline)
{
	cmdline->line = readline(PROMPT);
	if (!cmdline->line)
		return ;
	cmdline->len = ft_strlen(cmdline->line);
	if (cmdline->len > 0)
		add_history(cmdline->line);
	cmdline->i = 0;
}

void	print_tok(t_dlist *tokens)
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

void	minishell_start(t_line *cmdline)
{
	t_dlist	tokens;
	// t_dlist		cmd_list;

	ft_dlist_init(&tokens, tok_destroy);
	if (lex(cmdline, &tokens) != 0)
		return ;
	// if (parse(&tokens, &cmd_list) != 0)
	// 	return ;
	print_tok(&tokens);
	ft_dlist_destroy(&tokens);
}

void	print_env(t_dlist *env_start)
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

int	main(int ac, char **av, char **envp)
{
	t_line	cmdline;
	t_dlist	env_start;

	(void)ac;
	(void)av;
	if (set_env(&env_start, envp) != 0)
	{
		ft_dlist_destroy(&env_start);
		return (EXIT_FAILURE);
	}
	print_env(&env_start);
	ft_dlist_destroy(&env_start);
	while (1)
	{
		read_line(&cmdline);
		if (!cmdline.line)
			break ;
		minishell_start(&cmdline);
		free(cmdline.line);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
