#include "mini_shell.h"

t_copy *new_node(char *key, char *value)
{
    t_copy *new;

    new = malloc(sizeof(t_copy));
    if (!new)
        return (NULL);
    new->key = ft_strdup(key);
    new->value = ft_strdup(value);
    new->next = NULL;
    return (new);
}

void add_back(t_copy **list, t_copy *new_copy)
{
    t_copy *tmp;

	if (!*list)
		*list = new_copy;
	else
	{
		tmp = *list;
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = new_copy;
	}
}




t_copy *copy_env(char **envp)
{

    int i = 0;
    int j;
    char *key;
    char *value;
    t_copy *copy = NULL;

    while (envp[i])
    {
        j = 0;
        while (envp[i][j] && envp[i][j] != '=')
            j++;
        key = ft_substr(envp[i], 0, j);
        if (!key)
            return (NULL);
        value = ft_substr(envp[i], j + 1, ft_strlen(envp[i]) - j);
        if (!value)
            return (NULL);
        add_back(&copy, new_node(key, value));
        free(key);
        free(value);
        i++;
    }
    return (copy);
}
