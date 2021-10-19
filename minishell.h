#ifndef MINISHELL_H
# define MINISHELL_H
# include "./libft/includes/libft.h"
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

typedef struct	s_global
{
	int			pid;
}				t_global;
#endif
