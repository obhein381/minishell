# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jisulim <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/19 16:38:01 by jisulim           #+#    #+#              #
#    Updated: 2025/10/26 15:32:45 by jisulim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -I. -Isrcs/libft
AR      = ar
ARFLAGS = rcs

NAME    = libft.a

SRCS = \
	ft_atoi.c ft_isascii.c ft_memcpy.c ft_strlcat.c ft_strrchr.c \
	ft_bzero.c ft_isdigit.c ft_memmove.c ft_strlcpy.c ft_tolower.c \
	ft_calloc.c ft_isprint.c ft_memset.c ft_strlen.c ft_toupper.c \
	ft_isalnum.c ft_memchr.c ft_strchr.c ft_strncmp.c \
	ft_isalpha.c ft_memcmp.c ft_strdup.c ft_strnstr.c \
	ft_strjoin.c ft_strtrim.c ft_substr.c ft_split.c ft_itoa.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	ft_strmapi.c ft_striteri.c

BONUS_SRCS = \
	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS        = $(SRCS:.c=.o)

BONUS_OBJS  = $(BONUS_SRCS:.c=.o)

all: $(NAME)

BONUS_FLAG = .bonus_built

bonus: $(NAME) $(BONUS_FLAG)

$(BONUS_FLAG): $(NAME) $(BONUS_OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(BONUS_OBJS)
	@touch $(BONUS_FLAG)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c libft.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(BONUS_OBJS) $(BONUS_FLAG)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
