#include "../../parsing/mini_shell.h"


int handle_pwd(t_data *data)
{
    char *pwd;
	char *check;

	pwd = get_the_pathe(data->copy_env, "PWD=");
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
			printf("%s\n", check);
			free(check);
			return (0);
		}
	}
	t_copy *copy = data->copy_env;
	while (copy)
	{
		if (ft_strcmp(copy->key, "secret_pwd=") == 0)
		{
			printf("%s\n", copy->value);
			return (0);
		}
		copy = copy->next;
	}
	return (1);
}
