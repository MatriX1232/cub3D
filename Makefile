CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude/ -g

THREADS = $(shell nproc)
THREADS := $(shell expr $(THREADS))

NAME = cub3d

LIBFT = libft
MLX = mlx_linux

DEPS = $(MLX)/libmlx.a $(LIBFT)/libft.a

FILES = \
	src/main.c \


OBJS = ${FILES:.c=.o}

_BLUE=\e[34m
_PURPLE=\e[35m
_CYAN=\e[36m
_RED=\e[31m
_GREEN=\e[32m
_YELLOW=\e[33m
_WHITE=\e[37m
_BOLD=\e[1m
_ITALIC=\e[3m
_END=\e[0m

PADDING = 50

all: $(NAME)

%.o: %.c
	@printf "$(_CYAN)Compiling : $(_YELLOW)%-$(PADDING).$(PADDING)s\r$(_END)" $@
	@$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}


compile_dep: $(MLX) $(LIBFT)
	@printf "$(_CYAN)Compiling : $(_YELLOW)%-$(PADDING).$(PADDING)s$(_END)\n" "Libft"
	@+make -C $(LIBFT) --no-print-directory
	@printf "$(_CYAN)Compiling : $(_YELLOW)%-$(PADDING).$(PADDING)s$(_END)\n" "Minilibx"
	@+make -C $(MLX) --no-print-directory


$(NAME): compile_dep $(OBJS)
	@printf "$(_CYAN)Compiling : $(_YELLOW)%-$(PADDING).$(PADDING)s$(_END)\n" "Libft"
	@+make -C $(LIBFT) --no-print-directory
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(DEPS) $(LFLAGS) $(LIBFT)/libft.a
	@printf "$(_GREEN)Build complete: $(_ITALIC)$(_BOLD)$(_PURPLE)$(NAME)$(_END)\n"

clean:
	@+make -C $(LIBFT) clean --no-print-directory
	@+make -C $(MLX) clean --no-print-directory
	@rm -f $(OBJS)
	@printf "$(_CYAN)Removed all .o object files from: $(_GREEN)src/$(_END)\n"

fclean: clean
	@+make -C $(LIBFT) fclean --no-print-directory
	@+make -C $(MLX) fclean --no-print-directory
	@rm -f $(NAME)
	@printf "$(_CYAN)Removed executable: $(_PURPLE)$(NAME)$(_END)\n"

re:
	@printf "$(_YELLOW)Re-making project$(_END)\n"
	@+make fclean --no-print-directory
	@+make --no-print-directory

.PHONY: all clean fclean re
