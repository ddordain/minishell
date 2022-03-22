# defs

SRC =	src/main.c\
		src/lexer/lexer.c\
		src/lexer/lexer_utils.c\
		src/lexer/quote_check.c\
		src/lexer/token_utils.c\
		src/utils/ft_strlen.c

INC =	inc/minishell.h

OBJ =	$(SRC:.c=.o)

NAME =	minishell

CC =	gcc

CF =	-Wall -Wextra -Werror# -fsanitize=address -g3

CF2 =	-o $(NAME) -lreadline

RM =	rm -rf

# rules

%.o:	%.c $(INC)
		$(CC) $(CF) -c $< -o $@

all:	$(NAME)

$(NAME):$(OBJ) 
		$(CC) $(CF) $(OBJ) $(CF2)

clean:
		$(RM) $(OBJ)

fclean:	clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:	all clean fclean re bonus