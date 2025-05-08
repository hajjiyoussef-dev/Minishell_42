#include "../../parsing/mini_shell.h"


void update_env_value(t_copy *copy_env, char *str1, char *path)
{
	t_copy *curr;

	curr  = copy_env;
	while (curr)
	{
		if (ft_strcmp(curr->key, str1) == 0)
		{
			free(curr->value);
			curr->value = ft_strdup(path);
			return;
		}
		curr = curr->next;
	}
}

char *get_the_pathe(t_copy *copy_env, char *str)
{
	t_copy *curr;

	curr = copy_env;
	while (curr)
	{
		if (ft_strcmp(curr->key, str) == 0)
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
}

int handle_cd(char **argv, t_data *data)
{
	char *home;
	char *oldpwd;
	char cmd[PATH_MAX];


	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		perror("getcmd");
	
	// printf("%s \n", argv[1]);
	if (!argv[1])
	{
		printf("hhhhhhh \n");

		home = get_the_pathe(data->copy_env, "HOME");
		if (!home || chdir(home) != 0)
		{
			// ft_putstr_fd("minibash: ", STDERR_FILENO);
        	// ft_putendl_fd(argv[0], STDERR_FILENO);
			// ft_putstr_fd(": ", STDERR_FILENO);
			// ft_putendl_fd(argv[1], STDERR_FILENO);
			// ft_putstr_fd(": No such file or directory", STDERR_FILENO);
			return (1);
		}
	}
	else if (chdir(argv[1]) != 0)
	{
		// ft_putstr_fd("minibash: ", STDERR_FILENO);
		// ft_putendl_fd(argv[0], STDERR_FILENO);
		// ft_putstr_fd(": ", STDERR_FILENO);
		// ft_putendl_fd(argv[1], STDERR_FILENO);
		// ft_putstr_fd(": No such file or directory", STDERR_FILENO);
		return (1);
	}

	if (getcwd(cmd, sizeof(cmd)))
	{
		update_env_value(data->copy_env, "OLDPWD", oldpwd);
		update_env_value(data->copy_env, "PWD", cmd);
	}
	else
		return (1);

	return (0);
}
