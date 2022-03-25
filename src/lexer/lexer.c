/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:14:22 by pwu               #+#    #+#             */
/*   Updated: 2022/03/25 14:59:58 by pwu              ###   ########.fr       */
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

static int	check_format(const t_elem *cur_elem, const t_tok *cur_tok)
{
	t_tok	*next_tok;

	next_tok = cur_elem->next->data;
	if ((cur_tok->type == PIPE
			&& (!cur_elem->prev || (next_tok->type == EOF_TOK
					|| next_tok->type == PIPE)))
		|| ((cur_tok->type >= 3 && cur_tok->type <= 6)
			&& next_tok->type != WORD))
		return (write(2, "Syntax error: format\n", 21));
	return (0);
}

static int	tok_error(t_tok *token, const char *message)
{
	tok_destroy(token);
	if (message)
		write(2, message, ft_strlen(message));
	else
		perror("minishell");
	return (-1);
}

int	token_add(t_dlist *tokens, t_line *cmdline)
{
	t_tok	*token;

	token = malloc(sizeof(t_tok));
	if (!token)
		return (tok_error(NULL, NULL));
	token->content = NULL;
	token->type = NUL_TOK;
	while (is_space(cmdline->line[cmdline->i]))
		cmdline->i++;
	token->type = get_tok_type(cmdline);
	if (token->type == INVAL_OP)
		return (tok_error(token, "Syntax error: operator\n"));
	token->content = get_tok_content(cmdline, token->type);
	if (token->content == NULL)
		return (tok_error(token, NULL));
	if (ft_dlist_ins_next(tokens, ft_dlist_tail(tokens), token) == -1)
		return (tok_error(token, NULL));
	return (0);
}

int	lex(t_line *cmdline, t_dlist *tokens)
{
	t_elem	*cur_elem;
	t_tok	*cur_tok;

	if (quote_check(cmdline->line))
		return (write(2, "Syntax error: quote\n", 20));
	if (token_add(tokens, cmdline) != 0)
		return (-1);
	cur_elem = tokens->head;
	cur_tok = cur_elem->data;
	while (cur_tok->type != EOF_TOK)
	{
		if (token_add(tokens, cmdline) != 0
			|| check_format(cur_elem, cur_tok))
			return (-1);
		cur_elem = cur_elem->next;
		cur_tok = cur_elem->data;
	}
	return (0);
}
