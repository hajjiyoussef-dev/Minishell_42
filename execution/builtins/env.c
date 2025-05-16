#include "../../parsing/mini_shell.h"

void handle_env(t_data  *data)
{
    t_toke *tmp;
    t_copy *tmp_1;

    tmp = data->token;
    while (tmp)
    {
        if (!ft_strcmp("env", tmp->str))
        {
            tmp_1 = data->copy_env;
            while (tmp_1)
            {
                printf("%s=%s\n", tmp_1->key, tmp_1->value);
                tmp_1 = tmp_1->next;
            }
        }
        tmp = tmp->next;
<<<<<<< HEAD
    }
}
=======
    }   
}
>>>>>>> b6836bb24728ae25b705fab440d3ab3715d59138
