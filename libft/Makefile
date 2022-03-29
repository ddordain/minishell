# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddordain <ddordain@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/25 14:44:10 by ddordain          #+#    #+#              #
#    Updated: 2022/03/29 13:38:26 by ddordain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                   PROGRAM                                    #
# **************************************************************************** #

NAME = libft.a

# **************************************************************************** #
#                                   COMPILER                                   #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
ARFLAGS = -rcs

# **************************************************************************** #
#                                    PATHS                                     #
# **************************************************************************** #

INCS_PATH = include
SRCS_PATH = src
OBJS_PATH = obj

# **************************************************************************** #
#                                   SOURCES                                    #
# **************************************************************************** #

# SRCS DIRS
SRCS_CHAR_DIR = char
SRCS_STR_DIR = str
SRCS_MEM_DIR = mem
SRCS_NBR_DIR = nbr
SRCS_FD_DIR = fd
SRCS_LIST_DIR = list
SRCS_DLIST_DIR = dlist
SRCS_GNL_DIR = gnl

# OBJS DIR
OBJS_DIRS_NAME =	$(SRCS_CHAR_DIR) \
					$(SRCS_STR_DIR)	\
					$(SRCS_MEM_DIR)	\
					$(SRCS_NBR_DIR)	\
					$(SRCS_FD_DIR)	\
					$(SRCS_LIST_DIR) \
					$(SRCS_DLIST_DIR) \
					$(SRCS_GNL_DIR)

# OBJS DIRS IN OBJ PATH
OBJS_DIRS = $(addprefix $(OBJS_PATH)/, $(OBJS_DIRS_NAME))

# SRC FILES
SRCS_CHAR =	ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_tolower.c \
			ft_toupper.c

SRCS_STR =	ft_split.c \
			ft_strchr.c \
			ft_strdup.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strmapi.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_strcmp.c

SRCS_MEM =	ft_bzero.c \
			ft_calloc.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c

SRCS_NBR =	ft_atoi.c \
			ft_itoa.c

SRCS_FD =	ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c

SRCS_LIST =	ft_lstadd_back.c \
			ft_lstadd_front.c \
			ft_lstclear.c \
			ft_lstdelone.c \
			ft_lstiter.c \
			ft_lstlast.c \
			ft_lstmap.c \
			ft_lstnew.c \
			ft_lstsize.c

SRCS_DLIST =	ft_dlist_data.c \
				ft_dlist_destroy.c \
				ft_dlist_head.c \
				ft_dlist_init.c \
				ft_dlist_ins_next.c \
				ft_dlist_ins_prev.c \
				ft_dlist_is_head.c \
				ft_dlist_is_tail.c \
				ft_dlist_next.c \
				ft_dlist_prev.c \
				ft_dlist_remove.c \
				ft_dlist_size.c \
				ft_dlist_tail.c

SRCS_GNL =	get_next_line.c 

# SRC FILES AND SRCS DIRS
SRCS_NAME =	$(addprefix $(SRCS_CHAR_DIR)/, $(SRCS_CHAR)) \
			$(addprefix $(SRCS_STR_DIR)/, $(SRCS_STR)) \
			$(addprefix $(SRCS_MEM_DIR)/, $(SRCS_MEM)) \
			$(addprefix $(SRCS_NBR_DIR)/, $(SRCS_NBR)) \
			$(addprefix $(SRCS_FD_DIR)/, $(SRCS_FD)) \
			$(addprefix $(SRCS_LIST_DIR)/, $(SRCS_LIST)) \
			$(addprefix $(SRCS_DLIST_DIR)/, $(SRCS_DLIST)) \
			$(addprefix $(SRCS_GNL_DIR)/, $(SRCS_GNL))

# OBJS NAME
OBJS_NAME = $(SRCS_NAME:%.c=%.o)

# ADD PATH TO SRCS AND OBJS
SRCS = $(addprefix $(SRCS_PATH)/, $(SRCS_NAME));
OBJS = $(addprefix $(OBJS_PATH)/, $(OBJS_NAME));

# **************************************************************************** #
#                                    RULES                                     #
# **************************************************************************** #

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	ar $(ARFLAGS) $@ $^

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c | $(OBJS_DIRS)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCS_PATH)

$(OBJS_DIRS): | $(OBJS_PATH)
	mkdir -p $(OBJS_DIRS) 2> /dev/null

$(OBJS_PATH):
	mkdir -p $(OBJS_PATH) 2> /dev/null

clean:
	rm -rf $(OBJS_PATH)

fclean: clean
	rm -rf $(NAME)

re: fclean all
