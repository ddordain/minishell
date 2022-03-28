/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:52:05 by pwu               #+#    #+#             */
/*   Updated: 2022/03/28 15:45:49 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*alloc_error(char *s1, char *s2)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (NULL);
}

static char	*find_var(const t_dlist *env, const char *src, const int size)
{
	t_elem	*cur_elem;
	t_env	*cur_env;
	char	*res;

	if (src[0] == '?')
		return (ft_itoa((int)g_exit_status));
	cur_elem = env->head;
	while (cur_elem != NULL)
	{
		cur_env = cur_elem->data;
		if (ft_strncmp(cur_env->name, src, size) == 0
			&& ft_strlen(cur_env->name) == (size_t)size)
			return (ft_strdup(cur_env->value));
		cur_elem = cur_elem->next;
	}
	res = malloc(sizeof(char));
	if (!res)
		return (NULL);
	res[0] = 0;
	return (res);
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
	if (end == start + 1 && src[end] == '?')
		end++;
	var = find_var(env, src + start + 1, end - start - 1);
	if (!var)
		return (alloc_error(src, NULL));
	res = malloc(sizeof(char) * (ft_len(src) - end + start + ft_len(var) + 1));
	if (!res)
		return (alloc_error(src, var));
	i = -1;
	while (++i < start)
		res[i] = src[i];
	add_str(res, var, &i);
	add_str(res, src + end, &i);
	res[i] = 0;
	free(src);
	free(var);
	return (res);
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
				|| cur_tok->content[i + 1] == '_'
				|| cur_tok->content[i + 1] == '?') && quote != SQUOTE)
			cur_tok->content = expand_one(cur_tok->content, env, i--);
		if (!cur_tok->content)
			return (-1);
	}
	return (0);
}
