#include "../../parsing/mini_shell.h"


void	update_var(t_copy **env, char *key, char *value, int append)
{
	t_copy	*cur;
	char *new_val;

	cur = *env;
	while (cur)
	{
		if (!ft_strcmp(cur->key, key))
		{
			if (append)
			{
				new_val = ft_strjoin(cur->value, value + 1);
				cur->value = new_val;
			}
			else
			{
				free(cur->value);
				cur->value = ft_strdup(value);
			}
			return;
		}
		cur = cur->next;
	}
	add_back(env, new_node(ft_strdup(key), ft_strdup(value)));
}

void print_export(t_data *data)
{
	t_copy *tmp;
	char c = 'A';

	while (c <= 'Z')	
	{
		tmp = data->copy_env;
		while (tmp)
		{
			if (tmp->key[0] == c)
				printf("%s %s=%s\n", "declare -x", tmp->key, tmp->value);
			tmp = tmp->next;
		}
		c++;
	}
	c = 'a';
	while (c <= 'z')	
	{
		tmp = data->copy_env;
		while (tmp)
		{
			if (tmp->key[0] == c)
				printf("%s %s=%s\n", "declare -x", tmp->key, tmp->value);
			tmp = tmp->next;
		}
		c++;
	}
}

int handle_export(t_data *data)
{
	t_toke *tmp;
	int j;
	int k = 0;
	int append = 0;
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