# defs

SRC =	src/main.c\
		src/env/env.c\
		src/env/env_var_add.c\
		src/env/env_var_destroy.c\
		src/env/env_utils.c\
		src/lexer/lexer.c\
		src/lexer/lexer_utils.c\
		src/lexer/token_utils.c\
		src/error/error.c\
		src/parsing/parse.c\
		src/parsing/expansion.c\
		src/parsing/parse_utils.c\
		src/parsing/quote_remove.c\
		src/parsing/check_heredoc.c\
		src/parsing/command.c\
		src/parsing/cmd_add.c\
		src/parsing/cmd_redir.c\
		src/parsing/cmd_av.c\
		src/builtin/cd.c\
		src/builtin/export.c\
		src/debug.c\

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

.PHONY:	all clean fclean re bonus