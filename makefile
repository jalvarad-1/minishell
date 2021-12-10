NAME = minishell
SRC = 	main.c \
		signals_1.c \
		builtins_1.c \
		ft_echo.c \
		ft_pwd.c \
		ft_unset.c \
		ft_cd.c \
		ft_export.c \
		ft_env.c \
		ft_exit.c \
		parser_1.c \
		parser_2.c \
		lst_utils.c \
		pipex2.0.c \
		pipex2.0utils.c \
		get_inoutput.c \
		here_doc.c \
		parser_4.c \
		expand_01.c \
		expand_02.c \
		expand_03.c

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
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_DIR)$(LIBFT) -lreadline -L /Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/readline/include -o $(NAME)
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
