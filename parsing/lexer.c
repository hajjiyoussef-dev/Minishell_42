#include "mini_shell.h"

t_toke *create_token(char *str, char *type)
{
	t_toke *new_toke;

	new_toke = malloc(sizeof(t_toke));
	if (!new_toke)
		return (NULL);
	new_toke->str = ft_strdup(str);
	new_toke->type = ft_strdup(type);
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
		if (line[*i] != ' ' && line[*i] != '>' && line[*i] != '|' && line[*i] != '>' && line[*i] != '<')
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
    int start;
    int j = 0;
    char quote;
    char *word;

    quote = line[*i];
    (*i)++;
    start = *i;
    while (line[*i] && line[*i] != quote)
        (*i)++;
    word = malloc((*i - start) + 1);
    if (!word)
        return (NULL);
    while (start < *i)
        word[j++] = line[start++];
    word[j] = '\0';
    if (line[*i] == quote)
        (*i)++;
    return (word);
}
