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

typedef struct s_toke
{
    char *str;
    char *type;
    struct s_toke *next;
} t_toke;

t_toke  *create_token(char *str, char *type);
void    add_token(t_toke **list, t_toke *new_token);
char    *copy_word(char *line, int *i);
char    *copy_quoted_word(char *line, int *i);
char    *ft_strdup(char *str);

#endif