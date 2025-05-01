#ifndef MINI_SHELL
#define MINI_SHELL

# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <dirent.h>
# include <stdarg.h>
# include <termios.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <readline/history.h>
# include <readline/readline.h>


// for the execution 

typedef struct s_exec_cmd
{
	char **argv;
	char *infile;
	char *outfile ;
	int append;  // 1 if >> 0 if >
	int heredoc; 
} t_exec_cmd;

typedef enum s_type
{
	PIPE,
	WORD,
	DB_QT,
	SNL_QT,
	APPEND,
	REDIR_OUT,
	HEREDOC,
	REDIR_IN
} t_type;

typedef struct s_toke
{
	char	*str;
	t_type  type;
	int		space_after;
	struct	s_toke	*next;
} t_toke;

t_toke *create_token(char *str, t_type type, char spc_aftr);
void    add_token(t_toke **list, t_toke *new_token);
char    *copy_word(char *line, int *i);
char    *copy_quoted_word(char *line, int *i);
char    *ft_strdup(char *str);
char	*ft_strjoin(char *s1, char *s2);
char    *ft_substr(const char *s, int start, int len);
t_toke	*concatinate(t_toke *head);

#endif