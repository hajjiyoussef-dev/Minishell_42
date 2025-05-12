#include "../../parsing/mini_shell.h"

void	remove_var(t_copy *copy, char *key)
{
	t_copy	*cur;
	t_copy	*prev;

	cur = copy;
	prev = NULL;
	while (cur)
	{
		if (!ft_strcmp(cur->key, key))
		{
			if (!prev)
			copy = cur->next;
			else
			{
				printf("hnnnna\n");
				prev->next = cur->next;
			}
			free(cur);
			break ;
		}
		prev = cur;
		cur = cur->next;
	}
}

void	handle_unset(t_data  *data)
{
	t_toke	*tmp;

	tmp = data->token;
	while (tmp)
	{
		if (!ft_strcmp("unset", tmp->str) && tmp->next)
			remove_var(data->copy_env, tmp->next->str);
		tmp = tmp->next;
	}
}
