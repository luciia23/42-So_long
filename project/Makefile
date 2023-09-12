NAME = zelda

# ------- COLORS -------
NC				=	\033[0m
RED				=	\033[0;31m
GREEN			=	\033[0;32m
LRED			=	\033[1;31m
LGREEN			=	\033[1;32m
YELLOW			=	\033[1;33m
LBLUE			=	\033[1;34m
TITLE			=	\033[38;5;33m

BIN = bin
DIR_SRC = src
INCLUDE = -I inc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address -g3
CC = gcc $(CFLAGS) $(INCLUDE)

# ------- MLX -------
MLX_DIR = mlx
MLX_PATH = $(MLX_DIR)/libmlx.a
MLX_MAKE = Makefile
MFLAGS = -ldl -lmlx -L$(MLX_DIR) -lXext -lX11

# ------- LIBFT -------
LIBFT_DIR = libft
LIBFT_PATH = $(LIBFT_DIR)/libft.a
LIBFT_MAKE = Makefile
LFLAGS:= -L $(LIBFT_DIR) -lft
SFLAGS = -lSDL2 -L/usr/local/lib -lSDL2_mixer

VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose
VALGRIND_OUTFILE = valgrind-out.txt

SRC = 	main.c \
		map.c \
		window.c \
		sprite.c \
		image_utils.c \
		hooks.c \
		animation.c \
		init_img.c \
		score.c \
		sound.c \
		free_memory.c \
		game_management.c \
		game.c \

OBJS = $(SRC:%.c=$(BIN)/%.o)

# ------- RULES / TRIGGERS
all: $(NAME)

$(NAME) : $(LIBFT_PATH) $(MLX_PATH) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME) $(MFLAGS) $(SFLAGS)
	@echo "   - $(NAME) ${GREEN}compiled [OK]${NC}\n"

$(BIN)/%.o : $(DIR_SRC)/%.c
	@mkdir -p $(dir $@)
	@$(CC) -c $< -o $@

$(MLX_PATH):
	@make -C $(MLX_DIR)
	@echo "   - MINILIBX ${GREEN}compiled [OK]${NC}\n"

$(LIBFT_PATH):
	@cd $(LIBFT_DIR) && make
	@echo "   - LIBFT ${GREEN}compiled [OK]${NC}\n"

clean:
	@make -C $(LIBFT_DIR) -f $(LIBFT_MAKE) fclean
	@make -C $(MLX_DIR) -f $(MLX_MAKE) clean
	rm -rf $(BIN)

fclean: clean
	rm -rf $(OBJS) $(NAME)

re : fclean all

.PHONY: all re clean fclean