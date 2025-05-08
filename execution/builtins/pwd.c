#include "../../parsing/mini_shell.h"


int handle_pwd(t_toke *toke)
{
    t_toke *tmp;
	char *check;

    tmp = toke;
    while (tmp)
    {
        if (!ft_strcmp("pwd", tmp->str))
		{
			check = getcwd(NULL, 0);
            if (check != NULL)
			{
				printf("%s\n", getcwd(NULL, 0));
				return (0);
			}
			else
				return (1);
		}
        tmp = tmp->next;
    }
	return (1);
}