/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:13:14 by hrami             #+#    #+#             */
/*   Updated: 2025/06/22 17:36:20 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

extern volatile sig_atomic_t	g_sig;
typedef struct s_data			t_data;
typedef struct s_gc				t_gc;

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
}								t_type;

typedef struct s_toke
{
	char						*str;
	t_type						type;
	int							space_after;
	int							fd;
	int							is_spc;
	t_data						*data;
	struct s_toke				*next;
	struct s_toke				*prev;
}								t_toke;

typedef struct s_copy
{
	char						*key;
	char						*value;
	struct s_copy				*next;
}								t_copy;

typedef struct s_fd_track
{
	int							fd;
	struct s_fd_track			*next;

}								t_fd_track;

typedef struct s_data
{
	t_toke						*token;
	t_copy						*copy_env;
	t_gc						*gc;
	t_fd_track					*fd_tracker;
	int							last_exit_status;
	int							signal_status;
	t_toke						*cmd_start;
	bool						is_env_i;
	bool						heredoc_status;
}								t_data;

typedef struct s_gc
{
	void						*ptr;
	struct s_gc					*next;
}								t_gc;

typedef struct s_export
{
	int							append;
	int							egal;
	char						*key;
	char						*value;
}								t_export;

t_toke					*lexer(char *line);
t_toke					*create_token(char *str, t_type type,
							char spc_aftr);
void					add_token(t_toke **list, t_toke *new_token);
int						handle_space(char *line, int *i);
int						handle_pipe(char *line, int *i, t_toke **list);
int						handle_quotes(char *line, int *i,
							t_toke **list);
int						handle_redirections(char *line, int *i,
							t_toke **list);
void					handle_word(char *line, int *i, t_toke **list);
char					*copy_word(char *line, int *i);
char					*copy_quoted_word(char *line, int *i);
char					*ft_strdup(char *str);
char					*ft_strjoin(char *s1, char *s2);
char					*ft_substr(char *s, int start, int len);
t_toke					*concatinate(t_toke *head);
int						check_syntax(t_toke *tokens);
int						ft_strcmp(char *s1, char *s2);
void					expandd(t_toke *head, t_copy *copy,
							int checker);
char					*ft_strchr(const char *str, int c);
size_t					ft_strlen(char const *str);
char					*ft_joinchar(char *s, char c);
char					*get_str(char *str, t_copy *copy);
t_copy					*copy_env(char **envp, t_data *data);
char					*ft_itoa(int n);
long long				ft_atoi(const char *str, bool *overflow);
int						handle_file(t_data *data);
char					**ft_split(char const *s, char c);
void					split_word(t_toke **toke);
char					*expnand_it(char *str, t_copy *copy,
							int checker);
int						check_her_doc(t_toke *toke);
void					add_fd(t_fd_track **head, int fd);
void					close_all_fds(t_fd_track **head);
void					handle_wildcards(t_toke **list);
int						match_string(const char *file_name,
							const char *str);
char					**expand_wildcards(char *str, int *count);
char					**help_expand(char **matching, int *size,
							char *file_name);
void					sort_string_array(char **arr, int size);
char					*expand_line(char *line, t_data *data);
int						handle_heredoc(t_toke *toke, t_data *data);
void					expand_heredoc(t_toke **tmp);
int						ft_isalnum(char c);
int						ft_isalpha(int c);
void					ambiguous(t_toke **toke);
void					skip_doll(t_toke **toke);
int						is_spc(char *str);
void					add_back(t_copy **list, t_copy *new_copy);
t_copy					*new_node(char *key, char *value);
int						handle_pwd(t_data *data);
void					handle_env(t_data *data);
int						handle_export(t_data *data);
void					print_export(t_data *data);
void					update_var(t_copy **env, t_export *export);
void					update_env_value(t_copy *copy_env, char *str1,
							char *path);
void					print_getcwd_error(char *cmd);
int						handle_unset(t_toke *toke, t_copy **copy);
int						handle_cd(char **argv, t_data *data);
char					*get_the_pathe(t_copy *copy_env, char *str);
int						handle_echo(t_toke *start);
int						handle_exit(t_toke *tokns, t_toke *start,
							t_data *data);
void					signal_setup_child(void);
void					signal_setup(void);
void					sigint_handler(int sig);
void					signal_setup2(void);
void					sigint_handler2(int sig);
int						execute_cmds(t_data *data);
void					execute_cmd(t_data *data, t_toke *start,
							t_toke *end);
void					check_minishell_special_case(t_data *data);
int						handle_pipe_creation(t_toke *curr, int p_fds[2]);
int						handle_builtin_no_pipe(t_data *data,
							t_toke *cmd_start, t_toke *curr);
void					pipe_duping(int *p_read_end_fd, t_toke *curr,
							int p_fds[2]);
void					call_execute_cmd(t_data *data, t_toke *cmd_start,
							t_toke *curr);
void					pipe_check(int *p_read_end_fd, pid_t arr_pid[2],
							t_toke *curr, pid_t p_fds[2]);
void					wait_all_child(t_data *data, pid_t last_pid);
void					print_msg(char *arg, char *msg, int code);
char					*help_execute_cmd(t_data *data, char *cmd_path,
							char **argv);
void					exec_ve_scope(t_data *data, char *cmd_path,
							char **argv);
void					wait_all_child2(t_data *data, pid_t pid);
void					check_if_directory(char *cmd_path);
void					*gc_malloc(size_t size, int call);
void					*gc_realloc(char **matching, size_t old_size,
							size_t size);
char					*ft_get_argv_path_help(char *cmd, char **paths);
int						get_the_redirections(t_toke *start);
int						is_single_builtin_cmd(t_toke *start,
							t_toke *end);
int						execute_builtin(char **argv, t_data *data,
							t_toke *start);
bool					is_cmd_buitin(char *argv);
char					**env_list_to_array(t_copy *copy_envp);
char					*find_path(char *argv, char **ev,
							bool *is_path);
char					**build_argv(t_toke *cmd_start, t_toke *end_cmd,
							t_data *data);
char					*ft_strnstr(const char *haystack,
							const char *needle, size_t len);;
char					*ft_str_join(char *s1, char *s2);
char					*ft_str_dup2(const char *s1);
void					ft_putendl_fd(char *str, int fd);
void					ft_putstr_fd(char *str, int fd);
void					ft_putendl_fd_2(char *str, int fd);
#endif