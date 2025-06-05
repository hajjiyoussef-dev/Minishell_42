#include "../../parsing/mini_shell.h"

void	remove_var(t_copy **copy, char *key)
{
	t_copy	*cur;
	t_copy	*prev;
	char 	*join;

	cur = *copy;
	prev = NULL;
	join = ft_strjoin(key, "=");
	while (cur)
	{
		if (!ft_strcmp(cur->key, key) || !ft_strcmp(cur->key, join))
		{
			if (!prev)
				*copy = cur->next;
			else
				prev->next = cur->next;
			break;
		}
		prev = cur;
		cur = cur->next;
	}
}

int	handle_unset(t_toke *toke, t_copy **copy)
{
	t_toke	*tmp;
	t_toke	*arg;

	tmp = toke;
	while (tmp)
	{
		if (!ft_strcmp("unset", tmp->str) && tmp->next)
		{
			arg = tmp->next;
			while (arg && (arg->type == WORD || arg->type ==  DB_QT || arg->type == SNL_QT))
			{
				if (!ft_strcmp(arg->str, "_") || !ft_strcmp(arg->str, "secret_pwd"))
				{
					arg = arg->next;
					continue;
				}
				remove_var(copy, arg->str);
				arg = arg->next;
			}
			tmp = arg;
		}
		else
			tmp = tmp->next;
	}
	return (0);
}
