# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/16 11:50:59 by yzhan             #+#    #+#              #
#    Updated: 2024/07/04 15:21:26 by yzhan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FLAGS = -Wall -Wextra -Werror

SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c \
	ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
	ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c \
	ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
	ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
OBJ = $(SRC:.c=.o)

GNL_DIR = get_next_line
GNL_SRC = get_next_line.c get_next_line_utils.c
GNL_OBJ = $(addprefix $(GNL_DIR)/, $(GNL_SRC:.c=.o))

PTF_DIR = ft_printf
PTF_SRC = ft_printf.c ft_print_char.c ft_print_digit.c ft_print_pointer.c
PTF_OBJ = $(addprefix $(PTF_DIR)/, $(PTF_SRC:.c=.o))

%.o : %.c
	@cc $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(GNL_OBJ) $(PTF_OBJ)
	@ar -rc $@ $^

clean:
	@rm -f $(OBJ) $(GNL_OBJ) $(PTF_OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
