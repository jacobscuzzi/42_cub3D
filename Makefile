######### COLORS ########

GREEN := $(shell printf "\033[32m")
RED := $(shell printf "\033[31m")
BLUE := $(shell printf "\033[34m")
YELLOW := $(shell printf "\033[33m")
PINK := $(shell printf "\033[35m")
RESET := $(shell printf "\033[0m")
BOLD := $(shell printf "\033[1m")

######### UNICODE CHARS ########

CHECK := "✓"
ARROW := "➜"

######### VARIABLES ########


NAME			= cub3D

CC				= cc

LIBFT_PATH		= libft

LIBFT			= libft/libft.a

LIBFT_HEADER	= libft/includes/

STANDARD_FLAGS 	= -Wall -Werror -Wextra -I./includes -g3

MLX_FLAGS	= -I$(MLX_DIR) -L$(MLX_DIR) -lmlx -L/usr/lib/X11 -lXext -lX11

REMOVE = rm -rf





########## DIRECTORIES ##########

SRCS_DIR = srcs

SRCS_MAIN_DIR = $(SRCS_DIR)/main

SRCS_PARS_DIR = $(SRCS_DIR)/parsing

SRCS_RAY_DIR = $(SRCS_DIR)/raycasting

MLX_DIR         = ./mlx

OBJ_DIR = objs

INCLUDE_DIR = includes

INCLUDE_DIRS = -I$(INCLUDE_DIR) -I$(LIBFT_PATH)/includes

########## FILES ##########


SRC_FILES = $(SRCS_MAIN) $(SRCS_PARS) $(SRCS_RAY)

### MAIN ###
SRCS_MAIN = $(addprefix $(SRCS_MAIN_DIR)/, \
	main.c \
	clean_up.c)

### PARSING ###

SRCS_PARS = $(addprefix $(SRCS_PARS_DIR)/, \
	parsing.c\
	parsing_utils.c\
	check_input.c\
	check_input_tools.c\
	map_check.c\
	read_map.c\
	read_texture.c\
	read_color.c)

### RAYCASTING ###

SRCS_RAY = $(addprefix $(SRCS_RAY_DIR)/, \
	cub3d.c\
	drawing.c\
	mlx_tools.c\
	moves.c\
	raycaster.c\
	raycasting_utils.c\
	rays.c\
	toolbox.c)

### OBJECTS ###F

OBJ_FILES = $(patsubst %.c,$(OBJ_DIR)/%.o,$(notdir $(SRC_FILES)))


########## ANIMATION ##########

define TITLE
    @echo ""
    @echo "$(BOLD)$(PINK)   ██████╗██╗   ██╗██████╗     ██████╗ ██████╗ $(RESET)"
    @echo "$(BOLD)$(PINK)  ██╔════╝██║   ██║██╔══██╗    ╚════██╗██╔══██╗$(RESET)"
    @echo "$(BOLD)$(PINK)  ██║     ██║   ██║██████╔╝     █████╔╝██║  ██║$(RESET)"
    @echo "$(BOLD)$(PINK)  ██║     ██║   ██║██╔══██╗         ██╗██║  ██║$(RESET)"
    @echo "$(BOLD)$(PINK)  ╚██████╗╚██████╔╝██████╔╝    ██████╔╝██████╔╝$(RESET)"
    @echo "$(BOLD)$(PINK)   ╚═════╝ ╚═════╝ ╚═════╝     ╚══════╝╚═════╝ $(RESET)"
    @echo "$(GREEN)           Compilation Complete!            $(RESET)"
    @echo ""
endef

########## RULES ##########

all : ${NAME}


$(NAME): $(OBJ_FILES) $(LIBFT) ${MLX_DIR}/libmlx.a
		$(CC) ${STANDARD_FLAGS} -o $@ $^ -L$(LIBFT_PATH) -lm ${MLX_FLAGS}
		$(TITLE)


${LIBFT}:
	make -C $(LIBFT_PATH)

${MLX_DIR}/libmlx.a:
	make -C $(MLX_DIR)

$(OBJ_DIR)/%.o: $(SRCS_MAIN_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(STANDARD_FLAGS) $(INCLUDE_DIRS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRCS_PARS_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(STANDARD_FLAGS) $(INCLUDE_DIRS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRCS_RAY_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(STANDARD_FLAGS) $(INCLUDE_DIRS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@make fclean -C libft
	@make clean -C $(LIBFT_PATH)
	@make clean -C $(MLX_DIR)
	@$(REMOVE) $(OBJ_FILES)
	@$(REMOVE) $(OBJ_DIR)
	@echo "$(RED)$(BOLD)Cleaning up...$(RESET)"
	@echo "$(GREEN)$(BOLD)All clean!$(RESET)"


fclean: clean
	rm -f $(NAME)


re:			fclean all


valgrind:
			@valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(NAME) map/map_standard.bar

.PHONY:		all clean fclean re rebonus valgrind run run_bonus vallgrind compress
