# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/19 09:19:12 by mlamkadm          #+#    #+#              #
#    Updated: 2023/12/02 19:51:43 by mlamkadm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = libft.a

SRC =	ft_strlen.c ft_bzero.c\
		ft_putchar_fd.c\
		ft_putstr_fd.c ft_putnbr_fd.c ft_calloc.c\
		ft_strdup.c ft_atoi.c \

OBJ = $(SRC:.c=.o)

HEADER = libft.h

AR = ar -rcs

RM = rm -rf

all : $(NAME)

$(NAME) : $(OBJ)
	$(AR) $(NAME) $(OBJ)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)
	
re : fclean all

.PHONY : clean fclean re all
