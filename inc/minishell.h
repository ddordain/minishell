/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pwu <pwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 12:43:10 by pwu               #+#    #+#             */
/*   Updated: 2022/03/22 17:22:17 by pwu              ###   ########.fr       */
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

typedef struct s_command
{
	int					ac;
	char				**av;
	int					fdin;
	int					fdout;
}	t_command;

typedef struct s_line
{
	char	*line;
	int		len;
	int		i;
}	t_line;

typedef struct s_tok
{
	char			*content;
	int				type;
	struct s_tok	*next;
}	t_tok;

typedef struct s_tok_list
{
	t_tok	*tok_begin;
	int		tok_count;
}	t_tok_list;

/* functions */

/*	* lexer */
/*	*	* lexer master */
int		lex(t_line *cmdline, t_tok_list *tokens);

/*	*	* lexer utils */
bool	is_space(const char c);
bool	is_operator(const char c);
bool	is_type(const int type, const char c, int *quote_state);
int		find_operator(const char *line, const int start);

/*	*	* quote check */
int		quote_check(const char *line);

/*	*	* token utils*/
t_tok	*new_tok(char *content, const int tok_type);
int		clear_tok(t_tok *tok);
char	*get_tok_content(t_line *cmdline, const int tok_type);

/*	* utils */
int		ft_strlen(const char *s);

#endif		// MINISHELL_H