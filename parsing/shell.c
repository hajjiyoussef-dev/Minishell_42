#include "mini_shell.h"

int main(int ac, char **av, char **envp)
{
	t_toke *list;
	char *line;
	(void)ac;
	(void)av;
	t_data *data;
	int exit_status;
	rl_catch_signals = 0;

	data = NULL;
	if (!isatty(0) || !isatty(1))
		return (printf("test the project in the r\n"), 0);
	data = gc_malloc((sizeof(t_data)), 1);
	data->copy_env = copy_env(envp);
	signal_setup();
	while (1)
	{
		signal_setup();
		int	org_in = dup(0);
		add_fd(&data->fd_tracker, org_in);
		g_sig = 1;
		line = readline("minishell> ");
		if (g_sig == 42)
			data->last_exit_status = 130;
		if (!line)
		{
			printf("exit\n");
			dup2(org_in, 0);
			close(org_in);
			break ;
		}
		if (line[0])
			add_history(line);
		if (!(list = lexer(line)))
			data->last_exit_status = 2;
		expandd(list, data->copy_env, data->last_exit_status);
		split_word(&list);
		concatinate(list);
		handle_wildcards(&list);
		if (list)
			data->last_exit_status = check_syntax(list);
		if (data->last_exit_status == 0)
		{
			data->token = list;
			if (check_her_doc(list))
                return(printf("%s\n", "minishell: maximum here-document count exceeded"),free(line), 2);
			
			if (handle_file(data) == -1337)
			{
				dup2(org_in, 0);
				close(org_in);
				continue;
			}
			data->last_exit_status = execute_cmds(data);
		}
		free(line);
		dup2(org_in, 0);
		close(org_in);
	}
	exit_status = data->last_exit_status;
	gc_malloc(0, 0);
	return (exit_status);
}
