/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:52:05 by pwu               #+#    #+#             */
/*   Updated: 2022/04/20 15:19:22 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*find_var(t_minishell *sh, const char *src, const int size)
{
	t_elem	*cur_elem;
	t_env	*cur_env;
	char	*res;

	if (src[0] == '?')
		return (ft_itoa_ymalloc(sh, (int)g_exit_status));
	cur_elem = sh->dl_env.head;
	while (cur_elem != NULL)
	{
		cur_env = cur_elem->data;
		if (ft_strncmp(cur_env->name, src, size) == 0
			&& ft_strlen(cur_env->name) == (size_t)size)
			return (ft_strdup_ymalloc(cur_env->value, sh));
		cur_elem = cur_elem->next;
	}
	res = ymalloc(sizeof(char), sh);
	res[0] = 0;
	return (res);
}

static char	*expand_one(char *src, int *start, t_minishell *sh)
{
	char	*res;
	char	*var;
	int		end;
	int		i;

	end = *start + 1;
	while (ft_isalnum(src[end]) || src[end] == '_')
		end++;
	if (end == *start + 1 && src[end] == '?')
		end++;
	var = find_var(sh, src + *start + 1, end - *start - 1);
	res = ymalloc(
			sizeof(char) * (ft_len(src) - end + *start + ft_len(var) + 1), sh);
	i = -1;
	while (++i < *start)
		res[i] = src[i];
	add_str(res, var, &i);
	add_str(res, src + end, &i);
	res[i] = 0;
	*start = *start + ft_len(var);
	return (res);
}

void	var_expand(t_tok *cur_tok, t_elem *prev_elem, t_minishell *sh)
{
	int		i;
	int		quote;
	t_tok	*prev_tok;

	i = 0;
	if (prev_elem)
		prev_tok = prev_elem->data;
	if (cur_tok->type != WORD || (prev_elem && prev_tok->type == REDIR_HEREDOC))
		return ;
	quote = 0;
	while (cur_tok->content[i])
	{
		quote = quote_state(cur_tok->content[i], quote);
		if (cur_tok->content[i] == '$' && (ft_isalpha(cur_tok->content[i + 1])
				|| cur_tok->content[i + 1] == '_'
				|| cur_tok->content[i + 1] == '?') && quote != SQUOTE)
			cur_tok->content = expand_one(cur_tok->content, &i, sh);
		else
			i++;
	}
}
