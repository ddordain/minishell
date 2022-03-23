/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:00:52 by pwu               #+#    #+#             */
/*   Updated: 2022/03/23 13:23:17 by pwu              ###   ########.fr       */
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

void	print_tok(t_line *cmdline, t_tok_list *tokens)
{
	t_tok	*token;

	token = tokens->tok_begin;
	printf("line: $>%s\ntokens: %d\n\n", cmdline->line, tokens->tok_count);
	while (token != NULL)
	{
		printf("type: %d content: [%s]\n", token->type, token->content);
		token = token->next;
	}
}

void	minishell_start(t_line *cmdline)
{
	t_tok_list	tokens;
	// t_dlist		cmd_list;

	if (lex(cmdline, &tokens) != 0)
		return ;
	// if (parse(&tokens, &cmd_list) != 0)
	// 	return ;
	print_tok(cmdline, &tokens);
	clear_tok(tokens.tok_begin);
}

void	print_env(t_dlist *env_start)
{
	t_elem	*cur;
	t_env	*elem;

	cur = env_start->head;
	printf("environment variables: %d\n", env_start->size);
	while (cur != NULL)
	{
		elem = cur->data;
		printf("%s = %s\n", elem->name, elem->value);
		cur = cur->next;
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
	return (EXIT_SUCCESS);
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
