/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:33:25 by pwu               #+#    #+#             */
/*   Updated: 2022/04/06 16:22:27 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	get_tok_end(const t_line *cmdline, const int tok_type,
	int *tok_end)
{
	int	quote_state;

	quote_state = 0;
	*tok_end = cmdline->i;
	while (is_type(tok_type, cmdline->line[*tok_end], &quote_state))
		*tok_end = *tok_end + 1;
}

char	*get_tok_content(t_line *cmdline, const int tok_type, t_minishell *sh)
{
	int		end;
	char	*res;
	int		j;

	get_tok_end(cmdline, tok_type, &end);
	res = ymalloc(sizeof(char) * (end - cmdline->i + 1), sh);
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

void	tok_destroy(void *data)
{
	t_tok	*token;

	token = data;
	if (token)
	{
		if (token->content)
			free(token->content);
		free(token);
	}
}
