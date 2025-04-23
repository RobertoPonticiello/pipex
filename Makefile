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
	   pipex_utils.c \
	   moreutils.c \
	   moremoreutils.c \
	   get_next_line.c \
	   get_next_line_utils.c \
	   moremoremoreutils.c

OBJS = $(SRCS:.c=.o)
HEADER = pipex.h
FT_PRINTF_DIR = ft_printf
FT_PRINTF_LIB = $(FT_PRINTF_DIR)/libftprintf.a

all: $(NAME)

$(FT_PRINTF_LIB):
	$(MAKE) -C $(FT_PRINTF_DIR)

$(NAME): $(OBJS) $(FT_PRINTF_LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(FT_PRINTF_LIB)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(FT_PRINTF_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(FT_PRINTF_DIR) fclean
	rm -f $(NAME)

re: fclean all

debug: CFLAGS += -fsanitize=address
debug: re

.PHONY: all clean fclean re debug
