/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:52:05 by pwu               #+#    #+#             */
/*   Updated: 2022/03/25 15:13:58 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*find_var(const t_dlist *env, const char *src, const int size)
{
	t_elem	*cur_elem;
	t_env	*cur_env;

	cur_elem = env->head;
	while (cur_elem != NULL)
	{
		cur_env = cur_elem->data;
		if (ft_strncmp(cur_env->name, src, size) == 0
			&& ft_strlen(cur_env->name) == (size_t)size)
			return (cur_env->value);
		cur_elem = cur_elem->next;
	}
	return (NULL);
}

static char	*expand_one(char *src, const t_dlist *env, const int start)
{
	char	*res;
	char	*var;
	int		end;
	int		i;

	end = start + 1;
	while (ft_isalnum(src[end]) || src[end] == '_')
		end++;
	var = find_var(env, src + start + 1, end - start - 1);
	res = malloc(sizeof(char) * (ft_len(src) - end + start + ft_len(var) + 1));
	if (!res)
		return (NULL);
	i = -1;
	while (++i < start)
		res[i] = src[i];
	if (var)
		add_str(res, var, &i);
	add_str(res, src + end, &i);
	res[i] = 0;
	free(src);
	return (res);
}

static int	quote_state(const char c, int quote)
{
	if (c == '\'')
	{
		if (quote == 0)
			quote = SQUOTE;
		else if (quote == SQUOTE)
			quote = 0;
	}
	if (c == '\"')
	{
		if (quote == 0)
			quote = DQUOTE;
		else if (quote == DQUOTE)
			quote = 0;
	}
	return (quote);
}

int	var_expand(t_tok *cur_tok, const t_dlist *env)
{
	int	i;
	int	quote;

	i = -1;
	if (cur_tok->type != WORD)
		return (0);
	quote = 0;
	while (cur_tok->content[++i])
	{
		quote = quote_state(cur_tok->content[i], quote);
		if (cur_tok->content[i] == '$' && (ft_isalpha(cur_tok->content[i + 1])
				|| cur_tok->content[i + 1] == '_'))
		{
			cur_tok->content = expand_one(cur_tok->content, env, i);
			--i;
		}
		if (!cur_tok->content)
			return (-1);
	}
	return (0);
}
