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
	int		fd;
	struct	s_toke	*next;
} t_toke;

typedef struct s_copy
{
	char	*key;
	char	*value;
	struct	s_copy	*next;
} t_copy;


typedef struct s_data
{
	t_toke *token;
	t_copy *copy_env;
}	t_data;

t_toke *create_token(char *str, t_type type, char spc_aftr);
void    add_token(t_toke **list, t_toke *new_token);
char    *copy_word(char *line, int *i);
char    *copy_quoted_word(char *line, int *i);
char    *ft_strdup(char *str);
char	*ft_strjoin(char *s1, char *s2);
char    *ft_substr(const char *s, int start, int len);
t_toke	*concatinate(t_toke *head);
int		check_syntax(t_toke *tokens);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
int		ft_strcmp(char *s1, char *s2);
void	expandd(t_toke *head, t_copy *copy, int checker);
char	*ft_strchr(const char *str, int c);
size_t	ft_strlen(char const *str);
char	*ft_joinchar(char *s, char c);
char	*get_str(char *str, t_copy *copy);
t_copy	*copy_env(char **envp);
char	*ft_itoa(int n);
void	handle_file(t_toke *toke);
void	handle_pwd(t_toke *toke);
void	handle_env(t_toke *toke, t_copy *copy);
void	handle_export(t_toke *toke, t_copy *copy);
void	handle_unset(t_toke *toke, t_copy **copy);
char	**ft_split(char const *s, char c);
void	split_word(t_toke *toke);

#endif