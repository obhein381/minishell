CC      = cc
CFLAGS  = -Wall -Wextra -Werror -I. -Isrcs/libft

NAME = minishell

SRCS = srcs/debug/debug_token.c srcs/debug/debug_commands.c \
		srcs/main/build_commands.c srcs/main/main.c \
		srcs/lexer/tokenization.c srcs/lexer/tokenization_opt.c \
		srcs/parser/parser_redir.c srcs/parser/parser_pipe.c \
		srcs/parser/parser_word.c srcs/parser/parser_opt.c \
		srcs/parser/parser_syntax.c \
		srcs/parser/parser.c \
		srcs/executor/external/find_command_path.c srcs/executor/external/find_command_path_utils.c\
		srcs/executor/external/execute_external.c \
		srcs/executor/builtin/execute_builtin.c \
		srcs/executor/builtin/execute_echo.c \
		srcs/executor/executor.c

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
