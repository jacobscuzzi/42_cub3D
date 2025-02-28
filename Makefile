NAME			= cub3D

CC				= clang

CFLAG			= -Wall -Wextra -Werror

LIBFT_PATH		= libft/

LIBFT			= libft/libft.a

LIBFT_HEADER	= libft/includes/

STANDARD_FLAGS 	= -Wall -Werror -Wextra -I./includes

MLX_FLAGS	= -I$(MLX_DIR) -L$(MLX_DIR) -lmlx -L/usr/lib/X11 -lXext -lX11

REMOVE = rm -f

INCLUDE_DIR = includes

INCLUDE_DIRS = -I$(INCLUDE_DIR) -I$(LIBFT_PATH)/includes

SRCS_DIR = ./srcs/

OBJ_DIR = ./obj


OBJ_FILES = $(patsubst %.c,$(OBJ_DIR)/%.o,$(notdir $(SRCS)))

MLX_DIR         = ./mlx

FILES			= \
					main.c\
					parsing.c \
					new_game.c \
					mlx_hooks.c
				


SRCS			= $(addprefix $(SRCS_DIR), $(FILES))

all : ${NAME}

${MLX}

${LIBFT}:
		make -C $(LIBFT_PATH)

$(NAME): $(OBJ_FILES) $(LIBFT)
		@make -C $(MLX_DIR)
		@$(CC) $(SRCS) $(LIBFT) ${STANDARD_FLAGS}  ${MLX_FLAGS} -o ${NAME}

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJ_DIR)
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


run:		${NAME}
			${VALGRIND} ./${NAME} assets/maps/valid/map4.ber

valgrind:
			@valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(NAME) map/map_standard.bar

.PHONY:		all clean fclean re rebonus valgrind run run_bonus vallgrind
