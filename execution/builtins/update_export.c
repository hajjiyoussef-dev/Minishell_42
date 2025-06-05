#include "../../parsing/mini_shell.h"

void	add_new(t_copy **env, char *key, char *val, char *join, int append, int egal)
{
	if (append)
		add_back(env, new_node(ft_strdup(join), ft_strdup(val + 1)));
	else if (!egal)
		add_back(env, new_node(ft_strdup(key), ft_strdup(val)));
	else
		add_back(env, new_node(ft_strdup(join), ft_strdup(val)));
}


void	update_join_key(t_copy *cur, char *val, int append, int egal)
{
	char	*new_val;

	if (append)
	{
		new_val = ft_strjoin(cur->value, val + 1);
		cur->value = new_val;
	}
	else if (!egal && *val)
		cur->value = ft_strdup(val);
	else if (egal)
		cur->value = ft_strdup(val);
}

void	update_key_only(t_copy *cur, char *val, int append, int egal)
{
	char	*new_val;

	if (append)
	{
		cur->key = ft_strjoin(cur->key, "=");
		new_val = ft_strjoin(cur->value, val + 1);
		cur->value = new_val;
	}
	else if (!egal && *val)
		cur->value = ft_strdup(val);
	else if (egal)
	{
		cur->key = ft_strjoin(cur->key, "=");
		cur->value = ft_strdup(val);
	}
}



void	update_var(t_copy **env, char *key, char *value, int append, int egal)
{
	t_copy	*cur;
	char	*join;

	cur = *env;
	join = ft_str_join(key, "=");
	if(!ft_strcmp(key, "_") || !ft_strcmp(key, "secret_pwd"))
		return;
	while (cur)
	{
        if (!ft_strcmp(cur->key, join))
        {
        	update_join_key(cur, value, append, egal);
        	return ;
        }
        if (!ft_strcmp(cur->key, key))
        {
        	update_key_only(cur, value, append, egal);
        	return ;
        }
		cur = cur->next;
	}
	add_new(env, key, value, join, append, egal);
}
