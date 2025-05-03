#include "mini_shell.h"

t_toke *create_token(char *str, t_type type, char spc_aftr)
{
	t_toke *new_toke;

	new_toke = malloc(sizeof(t_toke));
	if (!new_toke)
		return (NULL);
	new_toke->str = ft_strdup(str);
	new_toke->type = type;
	if (spc_aftr == ' ')
		new_toke->space_after = 1;
	else
		new_toke->space_after = 0;
	new_toke->next = NULL;
	return (new_toke);
}

void add_token(t_toke **list, t_toke *new_token)
{
	t_toke *tmp;

	if (!*list)
		*list = new_token;
	else
	{
		tmp = *list;
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = new_token;
	}
}

char *copy_word(char *line, int *i)
{
	int start;
	int	j;
	char	*word;

	start = *i;
	while (line[*i])
	{
		if (line[*i] != ' ' && line[*i] != '>' && line[*i] != '|' && line[*i] != '\'' 
			&& line[*i] != '<' && line[*i] != '\"')
			(*i)++;
		else
			break ;
	}
	word = malloc((*i - start) + 1);
    if (!word)
		return (NULL);
	j = 0;
	while (start < *i)
		word[j++] = line[start++];
	word[j] = '\0';
	return (word);
}

char *copy_quoted_word(char *line, int *i)
{
    char    *result;
    int     start;
    char    quote;

    quote = line[*i];
    (*i)++;
    start = *i;
    while (line[*i] && line[*i] != quote)
        (*i)++;
    result = ft_substr(line, start, *i - start);
    // if (line[*i] == quote)
    //     (*i)++;
    return (result);
}
int	help_concatinate(t_type type)
{
	if (type == WORD || type == DB_QT || type == SNL_QT)
		return (1);
	return (0);
}
t_toke	*concatinate(t_toke *head)
{
	t_toke	*tmp;
	t_toke	*nxt;

	tmp = head;
	while (tmp && tmp->next)
	{
		nxt = tmp->next;
		while (nxt && help_concatinate(nxt->type) && help_concatinate(tmp->type)
				&& !tmp->space_after)
		{
			tmp->str = ft_strjoin(tmp->str, nxt->str);
			if (nxt && nxt->space_after)
			{
				nxt = nxt->next;
				break ;
			}
			nxt = nxt->next;
		}
		tmp->next = nxt;
		tmp = tmp->next;
	}
	return (head);
}
