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
	int k = 0;
	int append;
	char *key;
	char *value;
  
	tmp = data->token;
	while (tmp)
	{
		if (!ft_strcmp("export", tmp->str))
		{
			while (tmp->next && tmp->next->type == WORD)
			{
				k++;
				j = 0;
				if (!((tmp->next->str[j] >= 'a' && tmp->next->str[j] <= 'z') || (tmp->next->str[j] >= 'A' && tmp->next->str[j] <= 'Z')))
				{
					printf("minishell: export: `%s': not a valid identifier\n", tmp->next->str);
					return (0);	
				}
				while (tmp->next->str[j] && tmp->next->str[j] != '=')
            	{
					if (tmp->next->str[j] == '+' && tmp->next->str[j + 1] == '+')
					{
						printf("minishell: export: `%s': not a valid identifier\n", tmp->next->str);
						return (0);
					}
	        	    if (tmp->next->str[j] == '+' && tmp->next->str[j + 1] == '=')
	        	    {
	        	    	append = 1;
	        	    	break;
	        	    }
	        	    j++;
            	}
				key = ft_substr(tmp->next->str, 0, j);
				if (!key)
					return (1);
				value = ft_substr(tmp->next->str, j + 1, ft_strlen(tmp->next->str) - j);
				if (!value)
					return (free(key), 1);
				update_var(&data->copy_env, key, value, append);
				free(key);
				free(value);
				tmp->next = tmp->next->next;
			}
			if (!k)
				print_export(data);
		}
		tmp = tmp->next;
	}
	return (0);
}
