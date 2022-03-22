/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:00:52 by pwu               #+#    #+#             */
/*   Updated: 2022/03/21 16:58:29 by pwu              ###   ########.fr       */
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
	printf("line: '%s'\ntokens: %d\n\n", cmdline->line, tokens->tok_count);
	while (token != NULL)
	{
		printf("type: %d content: '%s'\n", token->type, token->content);
		token = token->next;
	}
}

void	minishell_start(t_line *cmdline)
{
	t_tok_list	tokens;
	// t_command	*cmd_start;

	if (lex(cmdline, &tokens) != 0)
		return ;
	print_tok(cmdline, &tokens);
	clear_tok(tokens.tok_begin);
}

int	main(int ac, char **av, char **envp)
{
	t_line		cmdline;

	(void)ac;
	(void)av;
	(void)envp;
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
