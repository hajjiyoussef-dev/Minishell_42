#include "../../parsing/mini_shell.h"


int handle_pwd(t_data *data)
{
    char *pwd;
	t_toke *tmp;
	char *check;

    tmp = data->token;
	pwd = get_the_pathe(data->copy_env, "PWD");
	if (pwd != NULL)
	{
		printf("%s\n", pwd);
		return (0);
	}
	else
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
	return (1);
}