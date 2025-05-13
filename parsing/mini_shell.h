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


#ifndef PATH_MAX
# define PATH_MAX 4096
#endif

typedef struct s_data t_data;

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
	t_data *data;

	struct	s_toke	*next;
	struct	s_toke	*prev;
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
	int    last_exit_status;
	int redirection_failed;
}	t_data;



t_toke *create_token(char *str, t_type type, char spc_aftr);
void    add_token(t_toke **list, t_toke *new_token);
char    *copy_word(char *line, int *i);
char    *copy_quoted_word(char *line, int *i);
char    *ft_strdup(char *str);
char	*ft_strjoin(char *s1, char *s2);
char    *ft_substr(char *s, int start, int len);
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
void	handle_file(t_toke *toke, t_data *data);
char	**ft_split(char const *s, char c);
void	split_word(t_toke *toke);

//builtins function !!!

void 	add_back(t_copy **list, t_copy *new_copy);
t_copy *new_node(char *key, char *value);
int 	handle_pwd(t_data *data);
void handle_env(t_toke *toke, t_copy *copy);
int handle_export(t_data *data);
void	handle_unset(t_toke *toke, t_copy **copy);
int 	handle_cd(char **argv, t_data *data);
char *get_the_pathe(t_copy *copy_env, char *str);
int handle_echo(t_data *data);


// end buitlins function !!!!!



// signals function

void signal_setup_child(void);
void signal_setup(void);

// end signal function !!!

// end of the test prasing header file 
// <==============================================================>
// the start of the  execution 

typedef struct s_exec_cmd
{
	char **argv;
	char *infile;
	char *outfile ;
	int append;  // 1 if >> 0 if >
	int heredoc; 
} t_exec_cmd;


typedef struct s_gc 
{
    void            *ptr;
    struct s_gc     *next;
}   t_gc;







// for the test ::
void execute_cmds(t_data *data);
void *gc_malloc(size_t size);
void free_gc_malloc(void);
char	*ft_get_argv_path_help(char *cmd, char **paths);

// copy of the envp in the t_data struct !!!


//same tools function 
char	*ft_str_chr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	**ft_sp_lit(char const *s, char c);
char	*ft_str_join(char *s1, char *s2);
char	*ft_str_dup2(const char *s1);
void ft_putendl_fd(char *str, int fd);
void ft_putstr_fd(char *str, int fd);
void ft_putendl_fd_2(char *str, int fd);

//end of the tools function 

#endif