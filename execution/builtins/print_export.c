#include "../../parsing/mini_shell.h"

static void	swap_env_nodes(t_copy *a, t_copy *b)
{
	char	*tmp_key;
	char	*tmp_val;

	tmp_key = a->key;
	tmp_val = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = tmp_key;
	b->value = tmp_val;
}

static void	sort_env(t_copy *env)
{
	t_copy	*cur;
	t_copy	*min;
	t_copy	*tmp;

	cur = env;
	while (cur)
	{
		min = cur;
		tmp = cur->next;
		while (tmp)
		{
			if (ft_strcmp(tmp->key, min->key) < 0)
				min = tmp;
			tmp = tmp->next;
		}
		if (min != cur)
			swap_env_nodes(cur, min);
		cur = cur->next;
	}
}

void	print_export(t_data *data)
{
	t_copy	*cur;

	if (!data->copy_env)
		return ;
	sort_env(data->copy_env);
	cur = data->copy_env;
    int count = 0;
    t_copy *tmp2 = data->copy_env;
    while (tmp2)
    {
        tmp2 = tmp2->next;
        count++;
    }
	while (cur)
	{
		if (ft_strcmp(cur->key, "_=") != 0)
		{
			if (count == 4 && !ft_strcmp(cur->key, "PATH="))
            {
                    cur = cur->next;
                    continue ;
            }
			if (!ft_strcmp(cur->key, "secret_pwd="))
			{
				cur = cur->next;
				continue ;
			}
			if (ft_strchr(cur->key, '='))
				printf("declare -x %s\"%s\"\n", cur->key, cur->value);
			else
				printf("declare -x %s\n", cur->key);
		}
		cur = cur->next;
	}
}
