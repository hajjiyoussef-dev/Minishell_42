/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:40:26 by yhajji            #+#    #+#             */
/*   Updated: 2025/05/02 19:03:32 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H 
#define TEST_H


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


typedef struct s_gc {
    void            *ptr;
    struct s_gc     *next;
}   t_gc;


typedef struct s_data
{
	char **envp;
	t_toke *tokens;

	char *pwd;
	char *oldpwd;
	
} t_data;




// for the test ::
void execute_cmds(t_data *data);
void *gc_malloc(size_t size);
void free_gc_malloc(void);
char	*ft_get_argv_path_help(char *cmd, char **paths);

// copy of the envp in the t_data struct !!!
char **copy_envp(char **envp);

//same tools function 
char	*ft_strchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	**ft_split(char const *s, char c);
char	*ft_str_join(char *s1, char *s2);


//end of the tools function 

#endif