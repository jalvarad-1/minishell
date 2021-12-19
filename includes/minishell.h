/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 16:16:33 by jalvarad          #+#    #+#             */
/*   Updated: 2021/12/19 12:10:49 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define CYAN "\033[0;36m"
# define RESET "\033[0m"
# define YELLOW "\033[0;33m"
# ifndef ARG_MAX
#  define ARG_MAX 20480
# endif
# ifndef READ_END
#  define READ_END 0
# endif
# ifndef WRITE_END
#  define WRITE_END 1
# endif
# include "../libft/includes/libft.h"
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

typedef struct s_global
{
	int			is_cmd;
	int			exit_status;
	int			pid;
	int			ctrl_c;
}				t_global;

t_global	g_common;

typedef struct s_parse
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
	int		aux_fds[2];
	int		status;
	pid_t	pid;
	char	*path;
	int		l_p;
	int		n_p;
}	t_pipe_var;

typedef struct s_fds
{
	char	*fds;
	int		is_hdoc;
	int		expand;
}	t_fds;

typedef struct s_cmds
{
	char			**content;
	t_fds			*input_fd;
	t_fds			*output_fd;
	char			*heredoc_end;
	struct s_cmds	*next;
}	t_cmds;

typedef struct s_iterator
{
	int		i;
	int		j;
	int		b;
	char	opr;
}	t_iterator;

void	rl_replace_line(const char *text, int clear_undo);
/*Signals*/
void	sig_handler(int signal);
void	signal_receiver(void);
void	son_signal(void);
void	parent_signal(void);
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
char	**change_var_value(char **dst, char *str, int j);
/*Parser*/
int		get_command_table(char *str, char **env, t_cmds **table);
int		operator_identifier(char **str);
int		rev_vertial_bars(char *str);
/*Lst utils*/
t_cmds	*ft_lstnew(char **content, t_fds *ins, t_fds *outs);
void	ft_lstadd_back(t_cmds **lst, t_cmds *new);
int		ft_lstsize(t_cmds *lst);
void	ft_free_table(t_cmds **table);
/*pipex*/
char	*search_path(char *argv, char **envp);
void	pipex(char ***envp, t_cmds *cmd);
t_fds	*ft_get_inputs(char ***token, char opr, char **env);
void	ft_heredoc(char *table, char **env, int expand, char *str);
void	make_out_redirections(t_pipe_var *info, t_fds *outputs);
void	make_in_redirections(t_pipe_var *info, t_fds *inputs, char **env);
void	kamikaze_sonX(t_pipe_var info, t_cmds *cmd, char ***envp);
void	kamikaze_son1(t_pipe_var info, t_cmds *cmd, char ***envp);
void	only_son(t_pipe_var info, t_cmds *cmd, char ***envp);
void	close_unnecessary(t_pipe_var info, int a, int b);
void	psycho_parent(t_pipe_var info, t_cmds *cmd, char ***envp);
void	close_unnecessary(t_pipe_var info, int a, int b);
void	distribute_work(t_pipe_var *info, t_cmds *aux, char ***envp, int i);
int		if_one_cmd(t_cmds *aux, t_pipe_var *info, char ***envp);
/*Expand $*/
void	ft_expand(char **token, char **env, int flag);
void	ft_dollar_detect(char **str, char **env, int flag);
size_t	*get_pos_dollar(size_t j, t_parse *prs, size_t **pos);
void	ft_dollar_expand(char **str, char **env, t_parse prs);
void	ft_seek_env(char **str, char **env, char **var);
void	get_env_value(char *aux, char *var, char **env, size_t *j);
void	get_exit_status(char *aux, size_t *j, char *var);
/*Trimming*/
int		ft_trim_quotes(char **str, int out);
char	**remove_ops_files(char **token, char opr);
char	*save_fd(char **token, int *i, int *j, char **env);
char	*save_hdoc_end(char **token, int *i, t_fds *fds);
int		redirection_counter(char **token, char opr);
int		fd_len(char *token);
void	mod_move_out_quotes(char *token, int *i);
char	*token_in_one_str(char **token, char optr);
void	get_shell_level(char ***env_v);

#endif
