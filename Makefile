NAME	= so_long
NAMEBONUS = so_long_bonus
CFLAGS	= -Wextra -Wall -Werror

LIBFT_DIR = ./LIBFT
LIBFT_A = $(LIBFT_DIR)/libft.a

LIBMLX_URL = https://github.com/codam-coding-college/MLX42.git
LIBMLX_DIR = ./MLX42
LIBMLX_A = $(LIBMLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm

HEADERS = -I $(LIBMLX_DIR)/include -I $(LIBFT_DIR)

SRCS	= main.c map_init.c map_check.c image_init.c image_draw.c hook.c player_move.c tools.c
OBJS	= $(SRCS:.c=.o)

BONUS_DIR = bonus
BONUS_SRCS = main_bonus.c map_init_bonus.c map_check_bonus.c path_check_bonus.c \
				image_init_bonus.c image_draw_bonus.c hook_bonus.c update_bonus.c \
				player_move_bonus.c enemy_move_bonus.c \
				tools_anima_bonus.c tools_delete_bonus.c tools_text_bonus.c
BONUS_OBJS = $(addprefix $(BONUS_DIR)/, $(BONUS_SRCS:.c=.o))

all: clone $(NAME)

bonus: clone $(NAMEBONUS)

clone:
	@if [ ! -d "$(LIBMLX_DIR)" ]; then \
		git clone $(LIBMLX_URL); \
	fi

%.o: %.c
	@cc $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS)
	@cmake $(LIBMLX_DIR) -B $(LIBMLX_DIR)/build && make -C $(LIBMLX_DIR)/build -j4
	@make -C $(LIBFT_DIR)
	cc $(OBJS) $(LIBFT_A) $(LIBMLX_A) -o $(NAME)

$(NAMEBONUS): $(BONUS_OBJS)
	@cmake $(LIBMLX_DIR) -B $(LIBMLX_DIR)/build && make -C $(LIBMLX_DIR)/build -j4
	@make -C $(LIBFT_DIR)
	cc $(BONUS_OBJS) $(LIBFT_A) $(LIBMLX_A) -o $(NAMEBONUS)

clean:
	@rm -rf $(OBJS) $(BONUS_OBJS)
	@rm -rf $(LIBMLX_DIR)/build
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@rm -rf $(NAME) $(NAMEBONUS)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus clone
