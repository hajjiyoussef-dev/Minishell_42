#include "../../parsing/mini_shell.h"

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
                if (!ft_strcmp(tmp_1->key, "secret_pwd="))
                {
                    tmp_1 = tmp_1->next;
                    continue ;
                }
                if (ft_strchr(tmp_1->key, '='))
                    printf("%s%s\n", tmp_1->key, tmp_1->value);
                tmp_1 = tmp_1->next;
            }
        }
        tmp = tmp->next;
    }   
}
