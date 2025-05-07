#include "mini_shell.h"


void handle_pwd(t_toke *toke)
{
    t_toke *tmp;

    tmp = toke;
    while (tmp)
    {
        if (!ft_strcmp("pwd", tmp->str))
            printf("%s\n", getcwd(NULL, 0));
        tmp = tmp->next;
    }   
}

void handle_env(t_toke *toke, t_copy *copy)
{
    t_toke *tmp;
    t_copy *tmp_1;

    tmp = toke;
    while (tmp)
    {
        if (!ft_strcmp("env", tmp->str))
        {
            tmp_1 = copy;
            while (tmp_1)
            {
                printf("%s=%s\n", tmp_1->key, tmp_1->value);
                tmp_1 = tmp_1->next;
            }
        }
        tmp = tmp->next;
    }   
}

void	remove_var(t_copy **copy, char *key)
{
	t_copy	*cur;
	t_copy	*prev;

	cur = *copy;
	prev = NULL;
	while (cur)
	{
		if (!ft_strcmp(cur->key, key))
		{
			if (!prev)
				*copy = cur->next;
			else
				prev->next = cur->next;
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
			remove_var(copy, tmp->next->str);
		tmp = tmp->next;
	}
}
