# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eherrero <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/03 14:32:58 by eherrero          #+#    #+#              #
#    Updated: 2020/03/09 16:51:04 by eherrero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=push_swap

CC=gcc

CFLAGS=-Wall -Wextra -Werror

RM=rm -f

LDFLAGS=-L.

LDLIBS=-lft

BMP=srcs/bmp.c

SRC=checks.c main.c not_valid.c orders.c stack.c stack2.c stack3.c utils.c stack_sorter.c

OBJ=$(SRC:.c=.o)

$(NAME):
	$(CC) $(CFLAGS) -o $(NAME) $(SRC) 

all: $(NAME)

bonus: $(NAME)

sanitize:
	$(CC) -g $(CFLAGS) -o $(NAME) $(SRC) -fsanitize=address 

clean:
	$(RM) $(OBJ) screenshot.bmp

fclean: clean
	$(RM) -rf $(NAME) $(NAME).dSYM

re: fclean all

.PHONY: clean fclean all bonus