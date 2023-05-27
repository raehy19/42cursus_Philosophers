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
CFLAGS := -Wall -Wextra -Werror -MMD -MP
RM := rm -f

all : $(NAME)

bonus : $(BONUS_NAME)

SRCS := \
	philo.c \
	ft_putstr_fd.c \

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
	$(CC) $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : all bonus clean fclean re
