/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:33:25 by pwu               #+#    #+#             */
/*   Updated: 2022/03/21 12:59:30 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tok	*new_tok(char *content, const int tok_type)
{
	t_tok	*res;

	if (!content)
		return (NULL);
	res = malloc(sizeof(t_tok));
	if (!res)
	{
		perror("minishell");
		free(content);
		return (NULL);
	}
	res->content = content;
	res->type = tok_type;
	res->next = NULL;
	return (res);
}

int	clear_tok(t_tok *tok)
{
	if (tok != NULL)
	{
		free(tok->content);
		clear_tok(tok->next);
		free(tok);
	}
	return (-1);
}

static void	get_tok_end(const t_line *cmdline, const int tok_type,
	int *tok_end)
{
	int	quote_state;

	quote_state = 0;
	*tok_end = cmdline->i;
	while (is_type(tok_type, cmdline->line[*tok_end], &quote_state))
		*tok_end = *tok_end + 1;
}

char	*get_tok_content(t_line *cmdline, const int tok_type)
{
	int		end;
	char	*res;
	int		j;

	get_tok_end(cmdline, tok_type, &end);
	res = malloc(sizeof(char) * (end - cmdline->i + 1));
	if (!res)
	{
		perror("minishell");
		return (NULL);
	}
	j = 0;
	while (cmdline->i < end)
	{
		res[j] = cmdline->line[cmdline->i];
		j++;
		cmdline->i++;
	}
	res[j] = 0;
	return (res);
}
