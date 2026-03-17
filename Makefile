CC      = cc
CFLAGS  = -Wall -Wextra -Werror -I. -Isrcs/libft

NAME = minishell

SRCS = srcs/main/main.c

OBJS = $(SRCS:.c=.o)

LIBFT_LIB  = srcs/libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) -lreadline -o $@

$(LIBFT_LIB):
	$(MAKE) -C srcs/libft

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C srcs/libft

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C srcs/libft

re: fclean all

.PHONY: all clean fclean re
