NAME	= so_long
CFLAGS	= -Wextra -Wall -Werror

LIBFT_DIR = LIBFT
LIBMLX_DIR = MLX42
LIBMLX_URL = https://github.com/codam-coding-college/MLX42.git
HEADERS = -I $(LIBMLX_DIR)/include -I $(LIBFT_DIR)
LIBMLX_A = $(LIBMLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm
LIBFT_A = $(LIBFT_DIR)/libft.a

SRCS	= main.c map_init.c map_check.c image_init.c image_draw.c hook.c player_move.c tools.c
OBJS	= $(SRCS:.c=.o)

all: clone $(NAME)

clone:
	@if [ ! -d "$(LIBMLX_DIR)" ]; then \
		git clone $(LIBMLX_URL); \
	else \
		echo "$(LIBMLX_DIR) already exists."; \
	fi

libmlx:
	@cmake $(LIBMLX_DIR) -B $(LIBMLX_DIR)/build && make -C $(LIBMLX_DIR)/build -j4

libft:
	@make -C $(LIBFT_DIR)

%.o: %.c
	@cc $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS) libmlx libft
	cc $(OBJS) $(LIBFT_A) $(LIBMLX_A) -o $@

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX_DIR)/build
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: clean all

.PHONY: all, clean, fclean, re, clone, libmlx, libft
