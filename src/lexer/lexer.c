/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:14:22 by pwu               #+#    #+#             */
/*   Updated: 2022/03/21 17:03:58 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	get_tok_type(const t_line *cmdline)
{
	if (is_operator(cmdline->line[cmdline->i]))
		return (find_operator(cmdline->line, cmdline->i));
	else if (cmdline->line[cmdline->i])
		return (WORD);
	else
		return (EOF_TOK);
}

static t_tok	*next_tok(t_line *cmdline)
{
	t_tok	*res;
	int		tok_type;

	while (is_space(cmdline->line[cmdline->i]))
		cmdline->i++;
	tok_type = get_tok_type(cmdline);
	if (tok_type == INVAL_OP)
	{
		write(2, "Syntax error: operator\n", 23);
		return (NULL);
	}
	res = new_tok(get_tok_content(cmdline, tok_type), tok_type);
	return (res);
}

static int	check_format(const t_tok *current_tok, const int tok_count)
{
	if ((current_tok->type == PIPE
			&& (tok_count == 1 || (current_tok->next->type == EOF_TOK
					|| current_tok->next->type == PIPE)))
		|| ((current_tok->type >= 3 && current_tok->type <= 6)
			&& current_tok->next->type != WORD))
		return (write(2, "Syntax error: format\n", 21));
	return (0);
}

int	lex(t_line *cmdline, t_tok_list *tokens)
{
	t_tok	*token;

	if (quote_check(cmdline->line))
		return (write(2, "Syntax error: quote\n", 20));
	tokens->tok_count = 0;
	tokens->tok_begin = next_tok(cmdline);
	if (!tokens->tok_begin)
		return (-1);
	token = tokens->tok_begin;
	tokens->tok_count++;
	while (token->type != EOF_TOK)
	{
		token->next = next_tok(cmdline);
		if (!token->next || check_format(token, tokens->tok_count))
			return (clear_tok(tokens->tok_begin));
		token = token->next;
		tokens->tok_count++;
	}
	return (0);
}
