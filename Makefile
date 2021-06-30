# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/02 14:55:32 by rkowalsk          #+#    #+#              #
#    Updated: 2021/06/29 14:52:35 by rkowalsk         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = \
	srcs/main.c \
	srcs/useful_lib.c \
	srcs/useful.c \
	srcs/philosophers.c \
	srcs/philo_eat.c \
	srcs/monitoring.c \
	srcs/init_table.c \
	srcs/args_parsing.c

OBJS = ${SRCS:.c=.o}

INCLUDES = philo.h

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	clang -o $(NAME) $(OBJS)

$(OBJS): %.o: %.c $(INCLUDES)
	clang -Wall -Wextra -Werror -g3 -I. -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
