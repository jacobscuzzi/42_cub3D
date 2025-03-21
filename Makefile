NAME			= cub3D

CC				= cc

LIBFT_PATH		= libft/

LIBFT			= libft/libft.a

LIBFT_HEADER	= libft/includes/

STANDARD_FLAGS 	= -Wall -Werror -Wextra -I./includes -g3

MLX_FLAGS	= -I$(MLX_DIR) -L$(MLX_DIR) -lmlx -L/usr/lib/X11 -lXext -lX11

REMOVE = rm -f

INCLUDE_DIR = includes

INCLUDE_DIRS = -I$(INCLUDE_DIR) -I$(LIBFT_PATH)/includes

SRCS_DIR = ./srcs/

MLX_DIR         = ./mlx

FILES			= $(shell find $(SRCS_DIR) -type f -name '*.c')

OBJ_FILES = $(FILES:.c=.o)

SRCS			= $(FILES)

all : ${NAME}

debug:
	@echo "Source files: $(FILES)"
	@echo "Object files that should be created: $(OBJ_FILES)"
	@echo "Object directory: $(OBJ_DIR)"
	@ls -la $(SRCS_DIR) || echo "Source directory issue!"
	@mkdir -p $(OBJ_DIR) && ls -la $(OBJ_DIR) || echo "Cannot create/access object directory!"


${LIBFT}:
	make -C $(LIBFT_PATH)

${MLX_DIR}/libmlx.a:
	make -C $(MLX_DIR)

%.o: %.c
	$(CC) $(STANDARD_FLAGS) $(INCLUDE_DIRS) -c $< -o $@

$(NAME): $(OBJ_FILES) $(LIBFT) ${MLX_DIR}/libmlx.a
		$(CC) $(OBJ_FILES) $(LIBFT) ${STANDARD_FLAGS} -lm ${MLX_FLAGS} -o ${NAME}


clean:
	make clean -C libft
	make clean -C $(LIBFT_PATH)
	make clean -C $(MLX_DIR)
	find $(SRCS_DIR) -name "*.o" -type f -delete
	rm -f $(NAME)

fclean: clean
	@make clean -C libft
	@make clean -C $(LIBFT_PATH)
	@make clean -C $(MLX_DIR)


re:			fclean all


valgrind:
			@valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(NAME) map/map_standard.bar

.PHONY:		all clean fclean re rebonus valgrind run run_bonus vallgrind compress
