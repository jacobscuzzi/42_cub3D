
NAME = libft.a

CC = cc

CFLAGS = -Werror -Wall -Wextra

FILES_LIBFT			= \
					ft_isalpha.c ft_isdigit.c ft_isalnum.c \
					ft_isascii.c ft_isprint.c ft_strlen.c \
					ft_memset.c ft_bzero.c ft_memcpy.c \
					ft_memmove.c ft_strlcpy.c ft_strlcat.c \
					ft_toupper.c ft_tolower.c ft_strchr.c \
					ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c \
					ft_strnstr.c ft_atoi.c ft_calloc.c \
					ft_strdup.c ft_substr.c ft_strjoin.c \
					ft_strtrim.c ft_split.c ft_itoa.c \
					ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
					ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
					ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
	  				ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
					ft_lstclear.c ft_lstiter.c ft_lstmap.c

FILES_PRINTF 		= \
					ft_printf.c ft_putchar_size.c ft_putnbr_hex_size.c \
					ft_putnbr_size.c ft_putnbr_uns_size.c ft_putpointer_size.c \
					ft_putstr_size.c

FILES_GNL			= \
					get_next_line.c get_next_line_utils.c

DIR_LIBFT			= srcs/srcs_libft/

DIR_PRINTF			= srcs/srcs_ft_printf/

DIR_GNL				= srcs/srcs_get_next_line/

SRCS				= \
					$(addprefix $(DIR_LIBFT), $(FILES_LIBFT)) \
					$(addprefix $(DIR_PRINTF), $(FILES_PRINTF)) \
					$(addprefix $(DIR_GNL), $(FILES_GNL))

OBJS	= $(SRCS:.c=.o)

HEADER		= includes/

all: $(NAME)

$(NAME): $(OBJS)
		@ar rcs $(NAME) $(OBJS)
		@echo $(NAME) "ready"

.c.o:
		@$(CC) $(CFLAGS) -c $< -o $@ -I$(HEADER)

clean:
	rm -f $(OBJS)
	@echo "Object Files deleted"


fclean: clean
		rm -f $(NAME)
		@echo $(NAME) "deleted"

re: fclean all


.PHONY: all clean fclean re
