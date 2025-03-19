NAME			= cub3D

CC				= cc

CFLAG			= -Wall -Wextra -Werror

LIBFT_PATH		= libft/

LIBFT			= libft/libft.a

LIBFT_HEADER	= libft/includes/

STANDARD_FLAGS 	= -Wall -Werror -Wextra -I./includes -g3

MLX_FLAGS	= -I$(MLX_DIR) -L$(MLX_DIR) -lmlx -L/usr/lib/X11 -lXext -lX11

REMOVE = rm -f

INCLUDE_DIR = includes

INCLUDE_DIRS = -I$(INCLUDE_DIR) -I$(LIBFT_PATH)/includes

SRCS_DIR = ./srcs/

OBJ_DIR = ./obj


OBJ_FILES		= $(patsubst $(SRCS_DIR)/%.c,$(OBJ_DIR)/%.o,$(FILES))

MLX_DIR         = ./mlx

# i have the files done with thhe find shell command
# However once we finish we need to add the files manually to the FILES variable, as the find command is maybe forbidden
FILES			= $(shell find $(SRCS_DIR) -type f -name '*.c')

SRCS			= $(FILES)

all : ${NAME}

${MLX}

${LIBFT}:
		make -C $(LIBFT_PATH)

$(NAME): $(OBJ_FILES) $(LIBFT)
		@make -C $(MLX_DIR)
		@$(CC) $(SRCS) $(LIBFT) ${STANDARD_FLAGS}  ${MLX_FLAGS} -o ${NAME}

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
		make clean -C libft
		@make clean -C $(LIBFT_PATH)
		@make clean -C $(MLX_DIR)

fclean:
		${REMOVE} ${NAME} ${BONUS}
		@make fclean -C $(LIBFT_PATH)
		@make clean -C $(MLX_DIR)
		@echo "${NAME}: ${NAME} were deleted${RESET}"

re:			clean all


valgrind:
			@valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(NAME) map/map_standard.bar

.PHONY:		all clean fclean re rebonus valgrind run run_bonus vallgrind compress
