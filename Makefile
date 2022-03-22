# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/15 15:05:08 by ddordain          #+#    #+#              #
#    Updated: 2022/03/22 13:31:23 by ddordain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean re fclean

NAME 		=	philo
OBJ_DIR		=	obj/
SRCS_DIR	=	src/
SRCS		=	lexer/lexer_utils.c \
				lexer/lexer.c \
				lexer/quote_check.c \
				lexer/token_utils.c \
				parsing/parse.c \
				main.c \
				

OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

LFLAGS = -I inc/
CFLAGS = -Wall -Wextra -Werror -pthread
DEBUGGING = -ggdb
CC = gcc
RM = rm -rf
AR = ar rc

RESET = \033[0m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
PINK = \033[35m
CYAN = \033[36m



all: $(NAME)

$(OBJ_DIR)%.o : $(SRCS_DIR)%.c
		@echo Create: $(NAME) Object directory
		@mkdir -p $(OBJ_DIR)
		$(CC) -c $(CFLAGS) $(DEBUGGING) $(LFLAGS) $< -o $@

$(NAME): $(OBJS)
		@echo "$(YELLOW)=========== Compilation $(NAME) ==========="
		$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)
		@echo "=========== DONE ==========$(RESET)"
clean:
		@echo "$(PINK)========== CLEAN =========="
		$(RM) $(OBJ_DIR)
		$(RM) $(OBJS)
		@echo "$(PINK)=========== DONE ===========$(RESET)"
fclean: clean
		@echo "$(RED)========== FCLEAN =========="
		$(RM) $(NAME)
		@echo "$(RED)=========== DONE ===========$(RESET)"
bonus: all
re: fclean all