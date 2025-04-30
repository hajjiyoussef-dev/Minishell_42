#include "mini_shell.h"

t_toke *lexer(char *line)
{
	int i = 0;
	t_toke *list;
	char	*word;
	int expecting_cmd = 1;

	list = NULL;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		else if (line[i] == '|')
		{
			add_token(&list, create_token("|", "PIPE"));
			expecting_cmd = 1;
			i++;
		}
		else if (line[i] == '\'' || line[i] == '\"')
		{
			word = copy_quoted_word(line, &i);
    		add_token(&list, create_token(word, "WORD"));
   			free(word);
		}
		else if ((line[i] == '>' && line[i + 1] == '>'))
		{
			add_token(&list, create_token(">>", "APPEND"));
			i += 2;
		}
		else if (line[i] == '>')
		{
			add_token(&list, create_token(">", "REDIR_OUT"));
			i++;
		}
		else if ((line[i] == '<' && line[i + 1] == '<'))
		{
			add_token(&list, create_token("<<", "HEREDOC"));
			i += 2;
		}
		else if (line[i] == '<')
		{
			add_token(&list, create_token("<", "REDIR_IN"));
			i++;
		}
		else
		{
			word = copy_word(line, &i);
			if (expecting_cmd)
				add_token(&list, create_token(word, "CMD"));
			else
				add_token(&list, create_token(word, "WORD"));
			expecting_cmd = 0;
			free(word);
		}
	}
	return (list);
}

void print_tokens(t_toke *list)
{
    while (list)
    {
        printf("STR: [%s] | TYPE: [%s]\n", list->str, list->type);
        list = list->next;
    }
}

int main()
{
	t_toke *list;
	char *line;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break;
		add_history(line);
		list = lexer(line);
		print_tokens(list);
	}
	return 0;
}