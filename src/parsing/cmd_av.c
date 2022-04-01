/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_av.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:05:41 by pwu               #+#    #+#             */
/*   Updated: 2022/04/01 13:22:37 by pwu              ###   ########.fr       */
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

static int	av_error(char **av)
{
	av_destroy(av);
	return (-1);
}

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

static char	**av_alloc(size_t size)
{
	char	**res;
	int		i;

	res = malloc(sizeof(char *) * size);
	if (!res)
		return (NULL);
	i = 0;
	while ((size_t)i < size)
	{
		res[i] = NULL;
		++i;
	}
	return (res);
}

int	av_add(t_command *cmd, t_dlist *tokens)
{
	t_elem	*cur_elem;
	t_tok	*cur_tok;
	int		i;

	cur_elem = tokens->head;
	cur_tok = cur_elem->data;
	cmd->ac = arg_count(tokens);
	i = 0;
	cmd->av = av_alloc(cmd->ac + 1);
	if (!cmd->av)
		return (-1);
	while (cur_tok->type != EOF_TOK && cur_tok->type != PIPE)
	{
		if (cur_tok->type == WORD)
		{
			cmd->av[i] = ft_strdup(cur_tok->content);
			if (!cmd->av[i])
				return (av_error(cmd->av));
			++i;
			cur_tok->type = NUL_TOK;
		}
		cur_elem = cur_elem->next;
		cur_tok = cur_elem->data;
	}
	return (0);
}
