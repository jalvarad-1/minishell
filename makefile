NAME = minishell
SRC = 	main.c \
		signals_1.c \
		builtins_1.c \
		ft_pwd.c \
		ft_unset.c

RED 			= \033[0;31m
GREEN 			= \033[0;32m
NONE 			= \033[0m

OBJ = $(SRC:.c=.o)
LIBFT_DIR = ./libft/
LIBFT = libft.a
HEADER = minishell.h

CFLAGS = -Wall -Wextra #-fsanitize=address #-Werror

all: proyect make-libft $(NAME) $(HEADER)
	@echo "Proyect $(NAME) ready!"

proyect:
	@echo "\t $(NAME) IS COMMING!!"

$(NAME): $(OBJ) $(HEADER)
	@echo "\t[ $(GREEN)✔$(NONE) ] compiling..."
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_DIR)$(LIBFT) -lreadline -o $(NAME)
	@echo "\t[ $(GREEN)✔$(NONE) ] $@ executable"

make-libft:
	@make -C $(LIBFT_DIR)

bonus: all

norm:
	norminette $(SRC) $(HEADER) $(LIBFT_DIR)

clean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	@rm -rf $(OBJ)

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@rm -rf $(NAME)
	@echo "\t[ $(RED)✗$(NONE) ] $(OBJ) recycle"
re: fclean all

.PHONY: all re m clean fclean bonus
