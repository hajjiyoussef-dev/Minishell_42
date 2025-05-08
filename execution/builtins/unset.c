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

void	handle_unset(t_toke *toke, t_copy **copy)
{
	t_toke	*tmp;

	tmp = toke;
	while (tmp)
	{
		if (!ft_strcmp("unset", tmp->str) && tmp->next)
			remove_var(*copy, tmp->next->str);
		tmp = tmp->next;
	}
}
