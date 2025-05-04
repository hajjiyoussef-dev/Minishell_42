/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:40:26 by yhajji            #+#    #+#             */
/*   Updated: 2025/05/04 06:11:19 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL
#define MINI_SHELL


#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>


// the test parsing
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

typedef struct s_exec_cmd t_exec_cmd;

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
void	expandd(t_toke *head, char **envp, int checker);
char	*ft_strchr(const char *str, int c);
size_t	ft_strlen(char const *str);
char	*ft_joinchar(char *s, char c);
char	*get_str(char *str, char **envp);
t_copy	*copy_env(char **envp);

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
char	*ft_str_nstr(const char *haystack, const char *needle, size_t len);
char	**ft_split(char const *s, char c);
char	*ft_str_join(char *s1, char *s2);
void ft_putendl_fd(char *str, int fd);
void ft_putstr_fd(char *str, int fd);

//end of the tools function 

#endif