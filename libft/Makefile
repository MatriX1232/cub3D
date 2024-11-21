CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_atoi.c ft_memchr.c ft_memcmp.c ft_calloc.c ft_strdup.c ft_strnstr.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_itoa.c ft_split.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strmapi.c ft_striteri.c
BONUS = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c ft_lstdelone.c
BONUSOBJS = $(BONUS:.c=.o)
OBJS = $(SRC:.c=.o)

_BLUE=\e[34m
_PURPLE=\e[35m
_CYAN=\e[36m
_RED=\e[31m
_GREEN=\e[32m
_YELLOW=\e[33m
_WHITE=\e[37m
_END=\e[0m

PADDING = 50


all: bonus

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@printf "$(_CYAN)Created libft library : $(_GREEN)%-$(PADDING).$(PADDING)s\n$(_END)" $(NAME)

%.o: %.c
	@printf "$(_CYAN)Compiling : $(_YELLOW)%-$(PADDING).$(PADDING)s\r$(_END)" $@
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS) $(BONUSOBJS)
	@printf "${_CYAN}Removed all .o object files from: $(_GREEN)libft/$(_END)\n"

fclean: clean
	@rm -rf $(NAME)
	@printf "${_CYAN}Removed library file: $(_GREEN)$(NAME)$(_END)\n"

re: fclean all

bonus: $(NAME) $(BONUSOBJS)
	@ar rcs $(NAME) $(BONUSOBJS)
	@printf "$(_CYAN)Created libft bonus : $(_GREEN)%-$(PADDING).$(PADDING)s\n$(_END)" $(NAME)

.PHONY: all clean fclean re bonus
