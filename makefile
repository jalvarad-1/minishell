NAME = minishell

# Source files #
SRC_FILES = main.c \
		builtins_1.c \
		builtins_ft_echo.c \
		builtins_ft_pwd.c \
		builtins_ft_unset.c \
		builtins_ft_cd.c \
		builtins_ft_export.c \
		builtins_ft_env.c \
		builtins_ft_exit.c \
		executer_pipex2.0.c \
		executer_pipex2.0utils.c \
		executer_out_redirections.c \
		executer_in_redirections.c \
		executer_here_doc.c \
		executer_sons1.c \
		executer_sons2.c \
		executer_one_cmds.c \
		parser_get_inoutput_1.c \
		parser_get_inoutput_2.c \
		parser_get_inoutput_3.c \
		parser_1.c \
		parser_2.c \
		expansion_trim_quotes.c \
		expansion_01.c \
		expansion_02.c \
		expansion_03.c \
		utils_shell_level.c \
		utils_signals_1.c \
		lst_utils.c \

OBJ_FILES = $(SRC_FILES:.c=.o)
# Directories #
SRC_DIR = srcs/
OBJ_DIR = obj/
HEADER_DIR = includes/

# Todo junto #
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

# Libft #
LIBFT_DIR = ./libft/
LIBFT = libft.a

# Includes #
HEADER = minishell.h

# Flags #
READLINE = -lreadline -L /Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/readline/include -o $(NAME)
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address
CC = gcc

all: make-libft $(NAME) 
	@echo "Proyect $(NAME) ready!"

$(NAME): $(OBJ) $(HEADER_DIR)$(HEADER)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_DIR)$(LIBFT) $(READLINE)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -I $(HEADER_DIR) -c $< -o $@

make-libft:
	@make -C $(LIBFT_DIR)

bonus: all

clean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	@rm -rf $(OBJ)

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@rm -rf $(NAME)
re: fclean all

.PHONY: all re m clean fclean bonus
