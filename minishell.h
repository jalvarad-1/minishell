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
# ifndef READ_END
#  define READ_END 0
# endif
# ifndef WRITE_END
#  define WRITE_END 1
# endif
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
	int			is_cmd;
	int			exit_status;
	int			pid;
}				t_global;

t_global g_common;

typedef struct	s_parse
{
	size_t	s_q;
	size_t	d_q;
	size_t	n_dollar;
	size_t	*pos_dollar;
}				t_parse;

typedef struct s_pipe_var
{
	int		fd1;
	int		size;
	int		**fd2;
	int		status;
	pid_t	pid;
	char	*path;
	int		l_p;/// last_pipe
	int		n_p;/// next_pipe
}	t_pipe_var;

typedef struct s_cmds
{
	char			**content;
	char			**input_fd;
	char			**output_fd; //Guardamos las redirecciones
	char			*heredoc_end;
	struct s_cmds	*next;
}	t_cmds;

void	rl_replace_line (const char *text, int clear_undo);
/*Signals*/
void	sig_handler(int signal);
void	signal_receiver(void);
/*Readline*/
char	*print_promt(void);
/*Built_ins*/
int		is_builtin(char **argv);
void	built_in_identifier(char **str, char ***env, int f_or_s);
void	ft_unset(char **str, char ***env, int f_or_s);
void	ft_pwd(int f_or_s);
void	ft_cd(char ***env_v, char **str, int f_or_s);
void	ft_export(char **str, char ***env, int f_or_s);
void	ft_env(char **env, bool assigned, int f_or_s);
void	ft_exit(char **str);
void	ft_echo(char **str, int f_or_s);
/*Generic utils*/
void	free_matrix(char **str);
int		locate_var(char **env, char *str);
char	*cut_compare(char *str);
char	**doublepointer_dup(char **array);
void	move_out_quotes(char **token, int i, int *j);
/*Parser*/
int		get_command_table(char *str, char **env, t_cmds **table);
void	ft_dollar_detect(char **str, char **env);
void	ft_trim_plus(char **str, t_parse prs);
int		operator_identifier(char **str);
/*Lst utils*/
t_cmds	*ft_lstnew(char **content);
void	ft_lstadd_back(t_cmds **lst, t_cmds *new);
int		ft_lstsize(t_cmds *lst);
void	ft_free_table(t_cmds **table);
/*pipex*/
char	*search_path(char *argv, char **envp);
void	pipex(char ***envp, t_cmds *cmd);
char	**ft_get_inputs(char ***token, char oprt);
#endif
