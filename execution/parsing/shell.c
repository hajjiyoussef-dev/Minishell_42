#include "../test.h"

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
			if (tmp == '\"')
    			add_token(&list, create_token(word, DB_QT, line[i + 1]));
			else
    			add_token(&list, create_token(word, SNL_QT, line[i + 1]));
   			free(word);
			i++;
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
	concatinate(list);
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


int main(int argc, char **argv, char **envp)
{
	t_toke *list;
	char *line;
	t_data *data = NULL;
	(void)argc;
	(void)argv;

	// copy the envp to the struct data for the execution parte (path) !!
	data = gc_malloc(sizeof(t_data));
	if (!data)
	{
		perror("failed malloc");
		exit(1);
	}
	// fprintf(stderr, "hanna1");
	data->envp = copy_envp(envp);
	// fprintf(stderr, "hanna2");
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break;
		add_history(line);
		list = lexer(line);
		data->tokens = list;
		// print_tokens(list);
		// execution parte !!!!
		execute_cmds(data);
	}
	return 0;
}