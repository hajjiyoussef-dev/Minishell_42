#include "../mini_shell.h"

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
        printf("STR: [%s] | TYPE: [%s] | bool: [%d]\n", head->str, token_type_to_str(head->type), head->space_after);
        head = head->next;
    }
}


// <<<<<<< execution
// =======
// void print_copy(t_copy *cpy)
// {
// 	t_copy *tmp = cpy;
// 	while (tmp)
// 	{
// 		printf("%s \n %s\n", tmp->key, tmp->value);
// 		tmp = tmp->next;
// 	}
// }
// >>>>>>> main
int main(int ac, char **av, char **envp)
{
	t_toke *list;
	char *line;
	static int checker;
	t_copy *copy;
	(void)ac;
	(void)av;
	t_data *data = NULL;

	data = gc_malloc((sizeof(t_data)));
	copy = copy_env(envp);
	data->copy_env = copy;
	while (1)
	{
		//signal function !!!
		signal_setup();
		line = readline("minishell$ ");
		if (!line)
			break;
		add_history(line);
		if (!(list = lexer(line)))
			checker = 2;
		// printf("%d\n", checker);
		expandd(list, envp, checker);
		concatinate(list);
		if (list)
		{
			checker = check_syntax(list);
		}
		// print_tokens(list);
		if (checker == 0)
		{
			data->token = list;
			execute_cmds(data);
		}
	}
	return 0;
}