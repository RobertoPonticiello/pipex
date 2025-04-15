# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: student <student@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/13 12:00:00 by student           #+#    #+#              #
#    Updated: 2025/04/13 12:00:00 by student          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRCS = pipex.c \
       utils.c \
       cmd_utils.c \
       path_utils.c \
       pipes_utils.c \
	   pipex_utils.c

OBJS = $(SRCS:.c=.o)
HEADER = pipex.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug: CFLAGS += -fsanitize=address
debug: re

.PHONY: all clean fclean re debug