/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 12:43:10 by pwu               #+#    #+#             */
/*   Updated: 2022/04/13 15:59:43 by pwu              ###   ########.fr       */
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
# include <sys/stat.h>
# include <signal.h>
// # include <sys/siginfo.h>
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
# define REDIR_APPEND 6		// >>
# define PIPE 7				// |
# define INVAL_OP 8

# define PIPE_RD 0
# define PIPE_WR 1

# define HANDLER_MAIN 0
# define HANDLER_RL 1
# define HANDLER_PARENT 2
# define HANDLER_CHILD 3

/* structs */

typedef struct s_line
{
	char		*line;
	int			len;
	int			i;
}	t_line;

typedef struct s_minishell
{
	t_dlist				dl_cmd;
	t_dlist				dl_tok;
	t_dlist				dl_env;
	t_dlist				dl_malloc;
	t_line				cmdline;
	struct sigaction	sa;
}	t_minishell;

typedef struct s_command
{
	int			ac;
	char		**av;
	char		**envp;
	t_dlist		redir;
	int			fdin;
	int			fdout;
	int			pipefd[2];
	pid_t		pid;
	t_minishell	*sh;
}	t_command;

typedef struct s_tok
{
	char		*content;
	int			type;
}	t_tok;

typedef struct s_env
{
	char		*name;
	char		*value;
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
t_elem	*get_env_elem(t_dlist *dl_env, char *name);
t_env	*get_env_data(t_dlist *dl_env, char *name);
char	*get_env_value(t_dlist *dl_env, char *name);
int		set_env_value(t_minishell *sh, char *name, char *new_value);
int		check_name(char *buffer_name, t_minishell *sh);

int		set_env(t_minishell *sh, char **envp);
int		env_var_add(t_minishell *sh, char *to_add);

/*	* lexer */
/*	*	* lexer master */
int		lex(t_minishell *sh);

/*	*	* lexer utils */
bool	is_space(const char c);
bool	is_operator(const char c);
bool	is_type(const int type, const char c, int *quote_state);
int		find_operator(const char *line, const int start);
int		quote_check(const char *line);

/*	*	* token utils*/
void	tok_destroy(void *data);
char	*get_tok_content(t_line *cmdline, const int tok_type, t_minishell *sh);

/*	* error utils */
void	pre_exec_error(const char *s, t_minishell *sh);
void	perror_exit(const char *str, t_minishell *sh);
void	*xmalloc(size_t bytes, t_minishell *sh);
void	*ymalloc(size_t bytes, t_minishell *sh);
char	*ft_strdup_ymalloc(const char *s, t_minishell *sh);
char	*ft_itoa_ymalloc(t_minishell *sh, int n);

/*	* parsing */
/*	*	* parser master */
void	parse(t_minishell *sh);

/*	*	* expansion */
void	var_expand(t_tok *cur_tok, t_elem *prev_elem, t_minishell *sh);

/*	*	* quote removal */
void	quote_remove(t_tok *cur_tok, t_minishell *sh);

/*	*	* parse utils */
int		ft_len(const char *s);
void	add_str(char *dst, const char *var, int *pos);
int		quote_state(const char c, int quote);
bool	is_quote(const char c, int *quote);

/*	*	* cmd making */
void	make_cmds(t_minishell *sh);
void	cmd_destroy(void *data);
void	cmd_add(t_minishell *sh);

/*	*	* cmd redir */
void	redir_add(t_command *cmd, t_minishell *sh);

/*	*	* cmd av */
void	av_add(t_command *cmd, t_minishell *sh);

/*	* exec */
/*	*	* exec master */
int		minishell_exec(t_minishell *sh);

/*	*	* exec cmd */
void	exec_cmd(t_elem *cur_elem, t_minishell *sh);
int		exec_redir(t_elem *elem, t_command *cmd);
int		exec_pipe(t_elem *elem, t_command *cmd);
int		exec_bin(t_elem *elem, t_command *cmd);

/*	*	* exec env */
char	**env_tab(t_dlist *dl_env);
char	**get_paths(t_dlist *dl_env);
char	*path_add_slash(char *s1);

/*	*	* exec utils */
int		ft_close(int *fd);
void	exec_close_fds(t_elem *elem);
void	minishell_exit(t_minishell *sh, int status);
int		str_tab_len(char **tab);
void	free_str_tab(char **tab, const int upto);

/*	* built-in */
void	builtin_cd(t_minishell *sh, t_command *cmd);
void	builtin_export(t_minishell *sh, t_command *cmd);
void	builtin_unset(t_dlist *dl_env, int ac, char **av);
void	builtin_exit(t_minishell *sh, t_line *cmdline);
void	builtin_echo(t_minishell *sh, t_command *cmd);

/*	* signal */
void	signal_handler(int handler, t_minishell *sh);
void	echo_on(void);

/*	* debug */
void	debug_print_env(t_dlist *env_start);
void	debug_print_tok(t_dlist *tokens);
void	debug_print_redir(t_command *cmd);
void	debug_print_av(t_command *cmd);
void	debug_print_cmd(t_dlist *cmds);
void	debug_print_tab(char **tab);
void	*rngalloc(size_t size);

#endif		// MINISHELL_H