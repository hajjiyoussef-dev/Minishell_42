#include "../../parsing/mini_shell.h"

int is_found(t_copy *copy, char *key)
{
    t_copy *tmp;

    tmp = copy;
    while (tmp)
    {
        if (!ft_strcmp(key, tmp->key))
            return(0);
        tmp = tmp->next;
    }
    return (1);
}

int handle_export(t_data *data)
{
	t_toke *tmp;
	int j;
	int append;
	char *key;
	char *value;

    tmp = toke;
    while (tmp)
    {
        if (!ft_strcmp("export", tmp->str) && tmp->next)
        {
            j = 0;
            while (tmp->next->str[j] && tmp->next->str[j] != '=')
                j++;
            key = ft_substr(tmp->next->str, 0, j);
            if (!is_found(copy, key))
                return(free(key), 1);
            if (!key)
                return (1);
            value = ft_substr(tmp->next->str, j + 1, ft_strlen(tmp->next->str) - j);
            if (!value)
                return (1);
            add_back(&copy, new_node(key, value));
            free(key);
            free(value);
        }
        tmp = tmp->next;
    }
    return (0);
}
