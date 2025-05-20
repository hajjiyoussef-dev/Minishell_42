#include "mini_shell.h"

t_copy *new_node(char *key, char *value)
{
    t_copy *new;

    new = malloc(sizeof(t_copy));
    if (!new)
        return(NULL);
    new->key = ft_strdup(key);
    new->value =ft_strdup(value);
    new->next = NULL;
    return (new);
}

void add_back(t_copy **list, t_copy *new_copy)
{
	t_copy *tmp;

	if (*list == NULL)
    {
		*list = new_copy;
    }
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_copy;
	}
}




t_copy *copy_env(char **envp)
{

    int i = 0;
    int j;
    char    *key;
    char    *value;
    static char    *k[]= {"PWD", "SHLVL", "_", NULL};
    static char    *v[] = {"/home/yhajji/Desktop/Minishell_42/parsing", "1", "/usr/bin/env", NULL};
    t_copy *copy = NULL;
    if (envp == NULL || envp[0] == NULL)
    { 
        printf("----\n");
        while (i < 3)
        {
            key = ft_strdup(k[i]);
            value = ft_strdup(v[i]);
            add_back(&copy, new_node(key, value));
            i++;
        }
        return (copy);
    }
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
// int is_found(t_copy *copy, char *key)
// {
//     t_copy *tmp;

//     tmp = copy;
//     while (tmp)
//     {
//         if (!ft_strcmp(key, tmp->key))
//             return(0);
//         tmp = tmp->next;
//     }
//     return (1);
// }

// int handle_export(t_toke *toke, t_copy *copy)
// {
//     t_toke *tmp;
//     int j;
//     char *key;
//     char *value;

//     tmp = toke;
//     while (tmp)
//     {
//         if (!ft_strcmp("export", tmp->str) && tmp->next)
//         {
//             j = 0;
//             while (tmp->next->str[j] && tmp->next->str[j] != '=')
//                 j++;
//             key = ft_substr(tmp->next->str, 0, j);
//             if (!is_found(copy, key))
//                 return(free(key), 1);
//             if (!key)
//                 return (1);
//             value = ft_substr(tmp->next->str, j + 1, ft_strlen(tmp->next->str) - j);
//             if (!value)
//                 return (1);
//             add_back(&copy, new_node(key, value));
//             free(key);
//             free(value);
//         }
//         tmp = tmp->next;
//     }
//     return (0);
// }