/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:34:47 by pwu               #+#    #+#             */
/*   Updated: 2022/04/01 15:09:46 by pwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	debug_print_env(t_dlist *env_start)
{
	t_elem	*cur_elem;
	t_env	*cur_data;

	cur_elem = env_start->head;
	printf("environment variables: %d\n\n", env_start->size);
	while (cur_elem != NULL)
	{
		cur_data = cur_elem->data;
		printf("%s = %s\n", cur_data->name, cur_data->value);
		cur_elem = cur_elem->next;
	}
}

void	debug_print_tok(t_dlist *tokens)
{
	t_elem	*cur_elem;
	t_tok	*cur_data;

	cur_elem = tokens->head;
	printf("tokens: %d\n\n", tokens->size);
	while (cur_elem != NULL)
	{
		cur_data = cur_elem->data;
		printf("type: %d content: [%s]\n", cur_data->type, cur_data->content);
		cur_elem = cur_elem->next;
	}
	printf("\n");
}

void	debug_print_redir(t_command *cmd)
{
	t_elem	*cur_elem;
	t_redir	*cur_data;

	cur_elem = cmd->redir.head;
	printf("redirs: %d\n", cmd->redir.size);
	while (cur_elem != NULL)
	{
		cur_data = cur_elem->data;
		printf("type: %d operand: [%s]\n", cur_data->type, cur_data->var);
		cur_elem = cur_elem->next;
	}
}

void	debug_print_av(t_command *cmd)
{
	printf("ac = %d\n", cmd->ac);
	for (int i = 0; i < cmd->ac; i++)
		printf("av[%d] = [%s]\n", i, cmd->av[i]);
}

void	debug_print_cmd(t_dlist *cmds)
{
	t_elem		*cur_elem;
	t_command	*cur_cmd;

	cur_elem = cmds->head;
	printf("cmds: %d\n\n", cmds->size);
	while (cur_elem != NULL)
	{
		cur_cmd = cur_elem->data;
		debug_print_redir(cur_cmd);
		debug_print_av(cur_cmd);
		cur_elem = cur_elem->next;
		printf("\n");
	}
}
