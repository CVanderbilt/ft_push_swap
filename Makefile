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

SRC=asort.c asort_aux1.c asort_aux2.c \
bsort.c checks.c evaluate.c main.c \
orders.c sorter.c stack1.c stack2.c stack3.c \
stack_sorter.c utils1.c utils2.c utils3.c utils4.c

OBJ=$(SRC:.c=.o)

$(NAME):
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC:.c=.o) 

all: $(NAME)

bonus: $(NAME)

sanitize:
	$(CC) -g $(CFLAGS) -o $(NAME) $(SRC) -fsanitize=address 

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) -rf $(NAME) $(NAME).dSYM

re: fclean all

.PHONY: clean fclean all bonus