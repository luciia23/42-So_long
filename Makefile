NAME = so_long

BIN = bin
DIR_SRC = src
INCLUDE = -I inc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address -g3
CC = gcc $(CFLAGS) $(INCLUDE)

# ------- MLX -------
MLX_DIR = mlx
MLX_PATH = $(MLX_DIR)/libmlx.a
MLX_MAKE = Makefile
MFLAGS = -ldl -lmlx -L${MLX_DIR} -framework OpenGL -framework AppKit -lz
# MFLAGS = -ldl -lmlx -L${MLX_DIR} -lXext -lX11

# ------- LIBFT -------
LIBFT_DIR = libft
LIBFT_PATH = $(LIBFT_DIR)/libft.a
LIBFT_MAKE = Makefile
LFLAGS:= -L $(LIBFT_DIR) -lft

SRC = 	main.c\
		check.c\
		map.c\
		utils.c\
		window.c\
		image.c

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