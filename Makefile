NAME = so_long
NAME_BONUS = so_long_bonus

BIN = bin/mandatory
DIR_SRC = src

BIN_BONUS = bin/bonus
DIR_SRC_BONUS = src_bonus
INCLUDE = -I inc
CFLAGS =  -g -fsanitize=address -g3
# VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose
CC = gcc $(CFLAGS) $(INCLUDE)
# ------- MLX -------
MLX_DIR = mlx_linux
MLX_PATH = $(MLX_DIR)/libmlx.a
MLX_MAKE = Makefile
# MFLAGS = -ldl -lmlx -L${MLX_DIR} -framework OpenGL -framework AppKit -lz
MFLAGS = -ldl -lmlx -L${MLX_DIR} -lXext -lX11

# ------- LIBFT -------
LIBFT_DIR = libft
LIBFT_PATH = $(LIBFT_DIR)/libft.a
LIBFT_MAKE = Makefile
LFLAGS:= -L $(LIBFT_DIR) -lft

# ------- COLORS -------
NC				=	\033[0m
RED				=	\033[0;31m
GREEN			=	\033[0;32m

SRC = 	main.c\
		check.c\
		map.c\
		init.c\
		valid_path.c\
		utils.c\
		window.c\
		image.c\
		free.c\
		hooks.c

SRC_BONUS = main_bonus.c\
			check_bonus.c\
			map_bonus.c\
			utils_bonus.c\
			window_bonus.c\
			init_bonus.c\
			image_bonus.c\
			panel_bonus.c\
			hooks_bonus.c

OBJS = $(SRC:%.c=$(BIN)/%.o)

OBJS_BONUS = $(SRC_BONUS:%.c=$(BIN_BONUS)/%.o)

# ------- RULES / TRIGGERS
all: $(NAME)

$(NAME) : $(LIBFT_PATH) $(MLX_PATH) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME) $(MFLAGS)
	@echo "   - $(NAME) ${GREEN}compiled [OK]${GREEN}\n"

$(BIN)/%.o : $(DIR_SRC)/%.c
	@mkdir -p $(dir $@)
	@$(CC) -c $< -o $@

$(MLX_PATH):
	@make -C $(MLX_DIR)
	@echo "   - MINILIBX ${GREEN}compiled [OK]${GREEN}\n"

$(LIBFT_PATH):
	@cd $(LIBFT_DIR) && make
	@echo "   - LIBFT ${GREEN}compiled [OK]${GREEN}\n"

bonus: $(NAME_BONUS)

$(NAME_BONUS) : $(LIBFT_PATH) $(MLX_PATH) $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LFLAGS) -o $(NAME_BONUS) $(MFLAGS)
	@echo "   - $(NAME_BONUS) ${GREEN}compiled [OK]${GREEN}\n"

$(BIN_BONUS)/%.o : $(DIR_SRC_BONUS)/%.c
	@mkdir -p $(dir $@)
	@$(CC) -c $< -o $@

clean:
	@make -C $(LIBFT_DIR) -f $(LIBFT_MAKE) fclean
	@make -C $(MLX_DIR) -f $(MLX_MAKE) clean
	rm -rf $(BIN)

fclean: clean
	rm -rf $(OBJS) $(NAME)
	rm -rf $(OBJS_BONUS) $(NAME_BONUS)

re : fclean all

.PHONY: all re clean fclean bonus