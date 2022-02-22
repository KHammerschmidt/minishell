# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: khammers <khammers@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/20 10:11:53 by katharinaha       #+#    #+#              #
#    Updated: 2022/02/05 14:22:52 by khammers         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Werror -Wextra

SRC = main_bonus.c \
	utils_bonus.c \
	pipex_bonus.c \
	here_doc_bonus.c

OBJECTS = $(SRC:.c=.o)
LIBFT_OBJ = ../lib/libft/libft.a

NAME = pipex

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT_OBJ)
	$(CC) $(FLAGS) $^ -o $@

$(LIBFT_OBJ):
	make --directory=./libft

clean:
	rm -f $(OBJECTS)
	make clean -C ./libft

fclean: clean
	rm -f $(NAME)
	make fclean -C ./libft

re: fclean all
