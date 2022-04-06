/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_av.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:05:41 by pwu               #+#    #+#             */
/*   Updated: 2022/04/06 17:24:19 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	av_destroy(char **av)
{
	int	i;

	i = 0;
	if (av)
	{
		while (av[i] != NULL)
		{
			free(av[i]);
			++i;
		}
		free(av);
	}
}

// static int	av_error(char **av)
// {
// 	av_destroy(av);
// 	return (-1);
// }

static int	arg_count(t_dlist *tokens)
{
	t_elem	*cur_elem;
	t_tok	*cur_tok;
	int		i;

	i = 0;
	cur_elem = tokens->head;
	cur_tok = cur_elem->data;
	while (cur_tok->type != EOF_TOK && cur_tok->type != PIPE)
	{
		if (cur_tok->type == WORD)
			++i;
		cur_elem = cur_elem->next;
		cur_tok = cur_elem->data;
	}
	return (i);
}

static char	**av_alloc(size_t size, t_minishell *sh)
{
	char	**res;
	int		i;

	res = ymalloc(sizeof(char *) * size, sh);
	i = 0;
	while ((size_t)i < size)
	{
		res[i] = NULL;
		++i;
	}
	return (res);
}

int	av_add(t_command *cmd, t_dlist *tokens, t_minishell *sh)
{
	t_elem	*cur_elem;
	t_tok	*cur_tok;
	int		i;

	cur_elem = tokens->head;
	cur_tok = cur_elem->data;
	cmd->ac = arg_count(tokens);
	i = 0;
	cmd->av = av_alloc(cmd->ac + 1, sh);
	while (cur_tok->type != EOF_TOK && cur_tok->type != PIPE)
	{
		if (cur_tok->type == WORD)
		{
			cmd->av[i] = ymalloc(ft_strlen(cur_tok->content) + 1, sh);
			ft_memcpy(cmd->av[i], cur_tok->content, ft_strlen(cur_tok->content));
			cmd->av[i][ft_strlen(cur_tok->content)] = 0;
			++i;
			cur_tok->type = NUL_TOK;
		}
		cur_elem = cur_elem->next;
		cur_tok = cur_elem->data;
	}
	return (0);
}
