# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/02 12:25:01 by sdeeyien          #+#    #+#              #
#    Updated: 2023/01/30 16:17:01 by sdeeyien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra
#CFLAGS =
UNAME_S := $(shell uname -s)
LIBDIR = libft
SRCDIR = src
DEPS = minitalk.h
NAME = minitalk

$(NAME): all

all:
	cd $(LIBDIR) && make
	$(CC) $(CFLAGS) $(SRCDIR)/server.c $(LIBDIR)/$(LIBDIR).a -o server
	$(CC) $(CFLAGS) $(SRCDIR)/client.c $(LIBDIR)/$(LIBDIR).a -o client

bonus:
	cd $(LIBDIR) && make
	$(CC) $(CFLAGS) $(SRCDIR)/server.c $(LIBDIR)/$(LIBDIR).a -o server
	$(CC) $(CFLAGS) $(SRCDIR)/client.c $(LIBDIR)/$(LIBDIR).a -o client

clean :
	rm -f client
	rm -f server
	make -C $(LIBDIR) clean

fclean : clean
	make -C $(LIBDIR) fclean

re : fclean all

.PHONY : all clean fclean re bonus
