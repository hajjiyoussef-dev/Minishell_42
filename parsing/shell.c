#include "mini_shell.h"

t_toke *lexer(char *line)
{
	int i = 0;
	t_toke *list;
	char	*word;
	char tmp;

	list = NULL;
	while (line[i])
	{
		if (line[i] == ' ' || (line[i] <= 13 && line[i] >= 9))
			i++;
		else if (line[i] == '|')
		{
			add_token(&list, create_token("|", PIPE, line[i + 1]));
			i++;
		}
		else if (line[i] == '\'' || line[i] == '\"')
		{
			tmp = line[i];
			word = copy_quoted_word(line, &i);
			if (line[i] == tmp)
				i++;
			else
				return (printf("minishell: syntax error you need close QT\n"), NULL);
			if (tmp == '\"')
    			add_token(&list, create_token(word, DB_QT, line[i]));
			else
    			add_token(&list, create_token(word, SNL_QT, line[i]));
   			free(word);
		}
		else if ((line[i] == '>' && line[i + 1] == '>'))
		{
			add_token(&list, create_token(">>", APPEND, line[i + 2]));
			i += 2;
		}
		else if (line[i] == '>')
		{
			add_token(&list, create_token(">", REDIR_OUT, line[i + 1]));
			i++;
		}
		else if ((line[i] == '<' && line[i + 1] == '<'))
		{
			add_token(&list, create_token("<<", HEREDOC, line[i + 2]));
			i += 2;
		}
		else if (line[i] == '<')
		{
			add_token(&list, create_token("<", REDIR_IN, line[i + 1]));
			i++;
		}
		else
		{
			word = copy_word(line, &i);
			add_token(&list, create_token(word, WORD, line[i]));
			free(word);
		}
	}
	return (list);
}

char *token_type_to_str(t_type type)
{
    if (type == WORD)
        return "WORD";
    if (type == PIPE)
        return "PIPE";
    if (type == REDIR_IN)
        return "REDIR_IN";
    if (type == REDIR_OUT)
        return "REDIR_OUT";
    if (type == APPEND)
        return "APPEND";
    if (type == HEREDOC)
        return "HEREDOC";
    if (type == DB_QT)
        return "DB_QT";
    if (type == SNL_QT)
        return "SNL_QT";
    return "UNKNOWN";
}

void print_tokens(t_toke *head)
{
    while (head)
    {
        printf("STR: [%s] | TYPE: [%s] | fd: [%d]\n", head->str, token_type_to_str(head->type), head->fd);
        head = head->next;
    }
}
char	*ft_strrchr(const char *s, int c)
{
	const char		*last_one;
	unsigned char	c1;

	last_one = NULL;
	c1 = (unsigned char)c;
	while (*s != '\0')
	{
		if (*s == c1)
		{
			last_one = s;
		}
		s++;
	}
	if (c1 == '\0')
		return ((char *)s);
	return ((char *)last_one);
}


char *minishell_name()
{
	char *cmd;
	char *name;
	char *new_cmd;
	char *result;
	char *result_2;
	char *result_3;
	char *colored;

	cmd = getcwd(NULL, 0);
	if (!cmd)
		return (NULL);
	name = ft_str_join(cmd, "$ ");
	free(cmd);
	if (!name)
		return (NULL);
	new_cmd = ft_strrchr(name, '/');
	if (!new_cmd)
		result = ft_strdup(name);  
	else
		result = ft_strdup(new_cmd + 1); 
	free(name);
	if (!result)
		return (NULL);

	colored = ft_str_join("\033[1;34m", result);    
	free(result);
	result = ft_str_join(colored, "\033[0m");       
	free(colored);
	colored = ft_str_join("\033[1;32m" , "->");
	result_2 = ft_str_join(colored, "\033[0m ");
	free(colored);
	result_3 = ft_str_join(result_2, result);
	return (result_3);
}


int main(int ac, char **av, char **envp)
{
	t_toke *list;
	char *line;
	(void)ac;
	(void)av;
	t_data *data = NULL;
	// some  shite 
	char *name;
	t_copy *copy = NULL;
	
	data = malloc((sizeof(t_data)));
	copy = copy_env(envp);
	data->copy_env = copy;
	printf("\033[2J\033[H");
	while (1)
	{
		signal_setup();
		// name = minishell_name();
		char *cmd = get_the_pathe(data->copy_env, "PWD");
		name = ft_str_join(cmd, "$ ");
		line = readline(name);
		if (!line)
			break ;
		add_history(line);
		if (!(list = lexer(line)))
			data->last_exit_status = 2;
		expandd(list, data->copy_env, data->last_exit_status);
		split_word(list);
		concatinate(list);
		if (list)
			data->last_exit_status = check_syntax(list);
		// print_tokens(list);
		if (data->last_exit_status == 0)
		{
			data->token = list;
			handle_file(data);
			execute_cmds(data);
		}
		// free(cmd);
		free(name);
	}
	return 0;
}
