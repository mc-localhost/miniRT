# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/13 13:17:30 by vvasiuko          #+#    #+#              #
#    Updated: 2025/04/03 10:12:36 by ykhattab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar
ARFLAGS = rcs
RM = rm -f
SRC = ft_atoi.c \
ft_atof.c \
ft_strlen.c \
ft_itoa.c \
ft_substr.c \
ft_bzero.c \
ft_calloc.c \
ft_isalnum.c \
ft_isalpha.c \
ft_isascii.c \
ft_isprint.c \
ft_isdigit.c \
ft_tolower.c \
ft_toupper.c \
ft_strncmp.c \
ft_strcmp.c \
ft_strjoin.c \
ft_strlcat.c \
ft_strlcpy.c \
ft_strnstr.c \
ft_strchr.c \
ft_strrchr.c \
ft_strdup.c \
ft_split.c \
ft_strmapi.c \
ft_striteri.c \
ft_strtrim.c \
ft_putchar_fd.c \
ft_putendl_fd.c \
ft_putnbr_fd.c \
ft_putstr_fd.c \
ft_putstr_stderr.c \
ft_memmove.c \
ft_memset.c  \
ft_memchr.c \
ft_memcmp.c \
ft_memcpy.c \
ft_lstadd_back.c \
ft_lstadd_front.c \
ft_lstclear.c \
ft_lstdelone.c \
ft_lstiter.c \
ft_lstlast.c \
ft_lstmap.c \
ft_lstnew.c \
ft_lstsize.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ)
	ranlib $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re