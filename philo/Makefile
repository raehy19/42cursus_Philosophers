# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/04 02:55:19 by rjeong            #+#    #+#              #
#    Updated: 2023/03/04 02:55:22 by rjeong           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo

CC := cc
CFLAGS := -Wall -Wextra -Werror -MMD -MP -O3 -fsanitize=thread -g
RM := rm -f

all : $(NAME)

SRCS := \
	philo.c \
	init.c \
	routine.c \
	time.c \
	act.c \
	act_utils.c \
	utils.c \
	time.c \
	ft_putstr_fd.c \
	ft_atoi.c \
	ft_calloc.c \

OBJS := \
	$(SRCS:.c=.o)

DEPS := \
	$(SRCS:.c=.d)

-include $(DEPS)

clean :
	$(RM) $(OBJS)
	$(RM) $(DEPS)

fclean : clean
	$(RM) $(NAME)

re : fclean
	make all

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : all clean fclean re
