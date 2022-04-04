/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 12:43:10 by pwu               #+#    #+#             */
/*   Updated: 2022/04/04 10:33:18 by ddordain         ###   ########.fr       */
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
# define REDIR_HEREDOC 5	// << limiter
# define REDIR_HEREDOC_RAW 6// << 'limiter'
# define REDIR_APPEND 7		// >>
# define PIPE 8				// |
# define INVAL_OP 9

/* structs */

typedef struct s_line
{
	char		*line;
	int			len;
	int			i;
}	t_line;

typedef struct s_minishell
{
	t_dlist	dl_cmd;
	t_dlist	dl_tok;
	t_dlist	dl_env;
}	t_minishell;

typedef struct s_command
{
	int			ac;
	char		**av;
	char		**envp;
	t_dlist		redir;
	int			fdin;
	int			fdout;
	int			pipein;
	int			pipeout;
	t_minishell	*sh;
}	t_command;

typedef struct s_tok
{
	char		*content;
	int			type;
	t_minishell	*sh;
}	t_tok;

typedef struct s_env
{
	char		*name;
	char		*value;
	t_minishell	*sh;
}	t_env;

typedef struct s_redir
{
	int		type;
	char	*var;
}	t_redir;

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
int		quote_check(const char *line);

/*	*	* token utils*/
void	tok_destroy(void *data);
char	*get_tok_content(t_line *cmdline, const int tok_type);

/*	* error utils */
void	perror_exit(const char *str, t_minishell *sh, t_line *cmdline);

/*	* parsing */
/*	*	* parser master */
int		parse(t_dlist *tokens, const t_dlist *env);

/*	*	* expansion */
int		var_expand(t_tok *cur_tok, const t_dlist *env, t_elem *prev_elem);

/*	*	* heredoc */
void	check_heredoc(t_tok *cur_tok, t_elem *prev_elem);

/*	*	* quote removal */
int		quote_remove(t_tok *cur_tok);

/*	*	* parse utils */
int		ft_len(const char *s);
void	add_str(char *dst, const char *var, int *pos);
int		quote_state(const char c, int quote);
bool	is_quote(const char c, int *quote);

/*	*	* cmd making */
int		make_cmds(t_dlist *tokens, t_dlist *commands);
void	cmd_destroy(void *data);
int		cmd_add(t_dlist *tokens, t_dlist *commands);

/*	*	* cmd redir */
void	redir_destroy(void *data);
int		redir_add(t_command *cmd, t_dlist *tokens);

/*	*	* cmd av */
int		av_add(t_command *cmd, t_dlist *tokens);
void	av_destroy(char **av);

/*	* built-in */
void	builtin_cd(t_dlist *dl_env, char *path);
void	builtin_export(t_dlist *dl_env, int ac, char **av);

/*	* debug */
void	debug_print_env(t_dlist *env_start);
void	debug_print_tok(t_dlist *tokens);
void	debug_print_redir(t_command *cmd);
void	debug_print_av(t_command *cmd);
void	debug_print_cmd(t_dlist *cmds);

#endif		// MINISHELL_H