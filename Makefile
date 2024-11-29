CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude/ -g
MLXFLAGSO = -I/usr/include -Imlx_linux -O3
MLXFLAGSN = -Lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -D LINUX -no-pie

NAME = cub3d

LIBFT = libft
MLX = mlx_linux

DEPS = $(MLX)/libmlx.a $(LIBFT)/libft.a

SRCS = \
	src/main.c \
	src/ft_images.c \
	src/anim.c \
	src/ft_draw.c \
	src/ft_minimap.c \
	src/ft_logs.c \
	src/ft_map_load.c \
	src/gnl.c \
	src/utils.c \
	src/ft_free.c \
	src/raycaster.c \
	src/input.c \
	src/splash_screen.c \
	src/HUD.c

OBJS = $(SRCS:%.c=%.o)

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
	@$(CC) $(CFLAGS) $(MLXFLAGSO) -c $< -o $@

$(NAME): compile_dep $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(DEPS) $(MLXFLAGSN) $(LIBFT)/libft.a
	@printf "$(_GREEN)Build complete: $(_ITALIC)$(_BOLD)$(_PURPLE)$(NAME)$(_END)\n"

compile_dep: $(MLX) $(LIBFT)
	@printf "$(_CYAN)Compiling : $(_YELLOW)%-$(PADDING).$(PADDING)s$(_END)\n" "Libft"
	@+make -C $(LIBFT) --no-print-directory
	@printf "$(_CYAN)Compiling : $(_YELLOW)%-$(PADDING).$(PADDING)s$(_END)\n" "Minilibx"
	@+make -C $(MLX) --no-print-directory

clean:
	@+make -C $(LIBFT) clean --no-print-directory
	@+make -C $(MLX) clean --no-print-directory
	@rm -rf $(OBJDIR)
	@printf "$(_CYAN)Removed all .o object files from: $(_GREEN)src/$(_END)\n"

fclean: clean
	@+make -C $(LIBFT) fclean --no-print-directory
	@+make -C $(MLX) clean --no-print-directory
	@rm -f $(NAME)
	@printf "$(_CYAN)Removed executable: $(_PURPLE)$(NAME)$(_END)\n"

re:
	@printf "$(_YELLOW)Re-making project$(_END)\n"
	@+make fclean --no-print-directory
	@+make --no-print-directory

.PHONY: all clean fclean re compile_dep
