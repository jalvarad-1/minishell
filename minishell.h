#ifndef MINISHELL_H
# define MINISHELL_H
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define CYAN "\033[0;36m"
# define RESET "\033[0m"
# define YELLOW "\033[0;33m"
#ifndef ARG_MAX
#define ARG_MAX 20480
#endif
# include "./libft/includes/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <stdbool.h>
# include <limits.h>

typedef struct	s_global
{
	int			pid;
}				t_global;
void	sig_handler(int signal);
void	signal_receiver(void);
char	*print_promt(void);
void	built_in_identifier(char *str, char ***env);
void	ft_unset(char **str, char ***env);
void	ft_pwd();
void	ft_cd(char ***env_v, char **str);
void	ft_export(char **str, char ***env);
void	ft_env(char **env, bool assigned);
int		locate_var(char **env, char *str);
char	*cut_compare(char *str);
#endif
