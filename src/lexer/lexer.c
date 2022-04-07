/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:14:22 by pwu               #+#    #+#             */
/*   Updated: 2022/04/07 12:19:34 by pwu              ###   ########.fr       */
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
		|| ((cur_tok->type >= REDIR_IN && cur_tok->type <= REDIR_APPEND)
			&& next_tok->type != WORD))
	{
		write(2, "Syntax error: format\n", 21);
		return (1);
	}
	return (0);
}

static int	lex_error(t_tok *token, const char *message)
{	
	tok_destroy(token);
	if (message)
	{	
		write(2, message, ft_strlen(message));
		return (1);
	}
	return (-1);
}

static int	token_add(t_minishell *sh)
{
	t_tok	*token;

	token = xmalloc(sizeof(t_tok), sh);
	token->content = NULL;
	token->type = NUL_TOK;
	while (is_space(sh->cmdline.line[sh->cmdline.i]))
		sh->cmdline.i++;
	token->type = get_tok_type(&sh->cmdline);
	if (token->type == INVAL_OP)
		return (lex_error(token, "Syntax error: operator\n"));
	if (ft_dlist_ins_next(&sh->dl_tok, ft_dlist_tail(&sh->dl_tok), token) == -1)
	{
		free(token);
		perror_exit("Malloc failure", sh);
	}
	token->content = get_tok_content(&sh->cmdline, token->type, sh);
	return (0);
}

int	lex(t_minishell *sh)
{
	t_elem	*cur_elem;
	t_tok	*cur_tok;
	int		err_code;

	if (quote_check(sh->cmdline.line))
		return (lex_error(NULL, "Syntax error: quote\n"));
	err_code = token_add(sh);
	if (err_code != 0)
		return (err_code);
	cur_elem = sh->dl_tok.head;
	cur_tok = cur_elem->data;
	while (cur_tok->type != EOF_TOK)
	{
		err_code = token_add(sh);
		if (err_code != 0)
			return (err_code);
		if (check_format(cur_elem, cur_tok))
			return (1);
		cur_elem = cur_elem->next;
		cur_tok = cur_elem->data;
	}
	return (0);
}
