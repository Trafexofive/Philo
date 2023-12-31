
CC := cc

NAME	:= philo

CFLAGS	:= -Wextra -Wall -Werror -g -fsanitize=thread

SRCS	:= main.c parse.c
LIBFT := libft/libft.a

OBJS	:= ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) -o $(NAME)

lib : 
	@make -C ./libft 

push:
	git add .
	git commit -m "Lazy_push"
	git push

%.o: %.c $(HEADERS) | lib
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C ./libft
	rm -rf $(OBJS)

fclean: clean
	make fclean -C ./libft
	rm -rf $(NAME)

re: fclean all

.PHONY: all, lib, push, clean, fclean, re
