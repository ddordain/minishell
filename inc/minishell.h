/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 12:43:10 by pwu               #+#    #+#             */
/*   Updated: 2022/03/28 15:52:05 by ddordain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* includes */

# include <stdbool.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <sys/types.h>
# include "../libft/include/libft.h"

/* defines */

//prompt
# define PROMPT "\033[1;33mminishell$>\033[0m"

//elements
# define NUL_TOK -2
# define EOF_TOK -1
# define WORD 0
# define SQUOTE 1			// '
# define DQUOTE 2			// "
# define REDIR_IN 3			// <
# define REDIR_TRUNC 4		// >
# define REDIR_HEREDOC 5	// <<
# define REDIR_APPEND 6		// >>
# define PIPE 7				// |
# define INVAL_OP 8

/* structs */

typedef struct s_minishell
{
	t_dlist	dl_cmd;
	t_dlist	dl_tok;
	t_dlist	dl_env;
}	t_minishell;

typedef struct s_command
{
	int		ac;
	char	**av;
	char	**envp;
	int		fdin;
	int		fdout;
	int		pipein;
	int		pipeout;
}	t_command;

typedef struct s_line
{
	char	*line;
	int		len;
	int		i;
}	t_line;

typedef struct s_tok
{
	char	*content;
	int		type;
}	t_tok;

typedef struct s_env
{
	char	*name;
	char	*value;
}	t_env;

/* global */

extern unsigned char	g_exit_status;

/* functions */

/*	* env */
int		set_env(t_dlist *env, char **envp);

t_env	*get_env_elem(t_dlist *dl_env, char *name);
char	*get_env_value(t_dlist *dl_env, char *name);
int		set_env_value(t_dlist *dl_env, char *name, char *new_value);
int		env_var_add(t_dlist *env, char *to_add);
void	env_var_destroy(void *data);

/*	* lexer */
/*	*	* lexer master */
int		lex(t_line *cmdline, t_dlist *tokens);

/*	*	* lexer utils */
bool	is_space(const char c);
bool	is_operator(const char c);
bool	is_type(const int type, const char c, int *quote_state);
int		find_operator(const char *line, const int start);

/*	*	* quote check */
int		quote_check(const char *line);

/*	*	* token utils*/
void	tok_destroy(void *data);
char	*get_tok_content(t_line *cmdline, const int tok_type);

/*	* error utils */
void	perror_exit(const char *str, t_minishell *sh);

/*	* parsing */
/*	*	* parser master */
int		parse(t_dlist *tokens, const t_dlist *env);

/*	*	* expansion */
int		var_expand(t_tok *cur_tok, const t_dlist *env);

int		ft_len(const char *s);
void	add_str(char *dst, const char *var, int *pos);
int		quote_state(const char c, int quote);

#endif		// MINISHELL_H