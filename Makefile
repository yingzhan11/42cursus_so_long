NAME	= so_long
CFLAGS	= -Wextra -Wall -Werror -Wunreachable-code -Ofast

HEADERS	= -I ./include -I $(LIBMLX)/include -I $(LIBFT)

LIBMLX	= ./MLX42
LIBFT = ./libft

LIBS	= $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a -ldl -lglfw -pthread -lm #libft.a 
KK = 
SRCS	= $(shell find ./src -iname "*.c") # not *
OBJS	= ${SRCS:.c=.o}

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@cc $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT)
	@cc $(OBJS) $(LIBFT)/libft.a $(LIBS) $(HEADERS) -o $(NAME) -Ofast

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build
	@$(MAKE) -C $(LIBFT) clean

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT) fclean

re: clean all

.PHONY: all, clean, fclean, re, libmlx