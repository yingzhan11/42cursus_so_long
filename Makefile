NAME	= so_long
CFLAGS	= -Wextra -Wall -Werror

LIBMLX	= MLX42
LIBFT = libft
HEADERS	= -I include -I $(LIBMLX)/include -I $(LIBFT)
LIBS	= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRCS_DIR = src
SRCS	= main.c map_init.c map_check.c image_init.c image_draw.c hook.c player_move.c tools.c
OBJS	= $(addprefix $(SRCS_DIR)/, $(SRCS:.c=.o))

MLX_URL = https://github.com/codam-coding-college/MLX42.git
MLX_DIR = MLX42

all: clone libmlx $(NAME)

clone:
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git clone $(MLX_URL); \
	else \
		echo "$(MLX_DIR) already exists."; \
	fi

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@cc $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT)
	@cc $(OBJS) $(LIBFT)/libft.a $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build
	@$(MAKE) -C $(LIBFT) clean

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT) fclean

re: clean all

.PHONY: all, clean, fclean, re, clone, libmlx