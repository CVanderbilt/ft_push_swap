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

BNAME=checker

CC=gcc

CFLAGS=-Wall -Wextra -Werror

RM=rm -f

LDFLAGS=-L.

LDLIBS=-lft

BMP=srcs/bmp.c

SRC=src/asort.c src/asort_aux1.c src/asort_aux2.c \
	src/bsort.c src/checks.c src/evaluate.c src/orders.c \
	src/sorter.c src/stack1.c src/stack2.c src/stack3.c \
	src/utils1.c src/utils2.c src/utils3.c src/utils4.c src/utils5.c\
	src/stack_sorter.c src/orders_aux.c

SRCMAIN=$(SRC) src/main.c

SRCBONUS=$(SRC) src/checker.c

OBJMAIN=$(SRCMAIN:.c=.o)

OBJBONUS=$(SRCBONUS:.c=.o)

$(NAME):
	$(CC) $(CFLAGS) -c $(SRCMAIN)
	mv *.o src/
	$(CC) $(CFLAGS) -o $(NAME) $(OBJMAIN)

$(BNAME):
	$(CC) $(CFLAGS) -c $(SRCBONUS)
	mv *.o src/
	$(CC) $(CFLAGS) -o $(BNAME) $(OBJBONUS) 

all: $(NAME)

bonus: $(BNAME)

sanitize:
	$(CC) -g $(CFLAGS) -o $(NAME) $(SRC) -fsanitize=address 

clean:
	$(RM) $(OBJMAIN) $(OBJBONUS)

fclean: clean
	$(RM) -rf $(NAME) $(NAME).dSYM
	$(RM) -rf $(BNAME) $(BNAME).dSYM

re: fclean all

.PHONY: clean fclean all bonus