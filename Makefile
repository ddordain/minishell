# defs

SRC =	src/main.c\
		src/env/env.c\
		src/env/env_var_add.c\
		src/env/env_utils.c\
		src/lexer/lexer.c\
		src/lexer/lexer_utils.c\
		src/lexer/token_utils.c\
		src/error/error.c\
		src/error/safe_malloc.c\
		src/parsing/parse.c\
		src/parsing/expansion.c\
		src/parsing/parse_utils.c\
		src/parsing/quote_remove.c\
		src/parsing/command.c\
		src/parsing/cmd_add.c\
		src/parsing/cmd_redir.c\
		src/parsing/cmd_av.c\
		src/parsing/heredoc.c\
		src/builtin/cd.c\
		src/builtin/unset.c\
		src/builtin/echo.c\
		src/builtin/export.c\
		src/builtin/export_utils.c\
		src/builtin/env.c\
		src/builtin/exit.c\
		src/builtin/pwd.c\
		src/debug/debug_print.c\
		src/debug/rngalloc.c\
		src/exec/exec_master.c\
		src/exec/exec_command.c\
		src/exec/exec_utils.c\
		src/exec/exec_redir.c\
		src/exec/exec_pipes.c\
		src/exec/exec_bin.c\
		src/exec/exec_env.c\
		src/exec/exec_parent.c\
		src/exec/launcher.c\
		src/signal/signal.c\

INC =	inc/minishell.h

OBJ =	$(SRC:.c=.o)

NAME =	minishell

LIBFT 		= 	libft.a

LIB_DIR		=	libft/

CC =	gcc

CF =	-Wall -Wextra -Werror -ggdb# -fsanitize=address -g3

CF2 =	-o $(NAME) -lreadline

RM =	rm -rf

# rules

%.o:	%.c $(INC)
		$(CC) $(CF) -c $< -o $@

all:	$(NAME)

$(NAME):$(OBJ) 
		make -C $(LIB_DIR)
		$(CC) $(CF) $(OBJ) $(CF2) $(LIB_DIR)$(LIBFT)
clean:
		$(RM) $(OBJ)
		make -C $(LIB_DIR) clean

fclean:	clean
		$(RM) $(NAME)
		make -C $(LIB_DIR) fclean

re:		fclean all

test: all
	valgrind \
	--leak-check=full \
	--track-origins=yes \
	--track-fds=yes \
	--show-leak-kinds=all \
	--show-reachable=yes \
	--suppressions=./.readline.supp \
	./minishell

.PHONY:	all clean fclean re bonus test