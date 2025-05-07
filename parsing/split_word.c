#include "mini_shell.h"

int is_spc(char *str)
{
    int i = 0;

    while (str[i] && str[i] == ' ')
        i++;
    if (str[i] == '\0')
        return (0);
    while (str[i] != ' ' && str[i])
        i++;
    if (str[i] == '\0')
        return (0);
    while (str[i] == ' ')
        i++;
    if (str[i] == '\0')
        return (0);
    return (1);
}

t_toke *new(char *str, t_type type, int flag)
{
	t_toke *new_toke;

	new_toke = malloc(sizeof(t_toke));
	if (!new_toke)
		return (NULL);
	new_toke->str = ft_strdup(str);
	new_toke->type = type;
	new_toke->fd = -1;
    new_toke->space_after = flag;
	new_toke->next = NULL;
	return (new_toke);
}

void add_node(t_toke *toke, char **str, int count)
{
    t_toke *tmp = toke;
    t_toke *after;
    int i = 0;
    int space;

    while (tmp && i++ < count)
        tmp = tmp->next;
    if (!tmp || !str || !str[0])
        return;
    after = tmp->next; 
    free(tmp->str);
    space = tmp->space_after;
    tmp->str = ft_strdup(str[0]);
    tmp->space_after = 1;
    i = 1;
    while (str[i])
    {
        if (!str[i + 1])
            tmp->next = new(str[i], WORD, space);
        else
            tmp->next = new(str[i], WORD, 1);
        tmp = tmp->next;
        i++;
    }
    tmp->next = after;
    i = 0;
    while (str[i])
        free(str[i++]);
    free(str);
}

void split_word(t_toke *toke)
{
    t_toke *tmp = toke;
    char **split;
    int i = 0;

    while (tmp)
    {
        if (tmp->type == WORD && is_spc(tmp->str))
        {
            split = ft_split(tmp->str, ' ');
            if (split)
            {
                add_node(toke, split, i);
                tmp = toke;
                i = 0;
                continue ;
            }
        }
        tmp = tmp->next;
        i++;
    }
}
