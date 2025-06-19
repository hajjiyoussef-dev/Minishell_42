#include "../../parsing/mini_shell.h"

void update_env_value(t_copy *copy_env, char *str1, char *path)
{
	t_copy *curr;

	curr  = copy_env;
	while (curr)
	{
		if (ft_strcmp(curr->key, str1) == 0)
		{
			curr->value = ft_strdup(path);
			return;
		}
		curr = curr->next;
	}
	add_back(&copy_env, new_node(ft_strdup(str1), ft_strdup(path)));
	while (curr)
	{
		if (!ft_strcmp(curr->key, "secret_pwd="))
		{
			curr->value = ft_strdup(path);
			return ;
		}
		curr = curr->next;
	}
	add_back(&copy_env, new_node(ft_strdup("secret_pwd="), ft_strdup(path)));
}

char *get_the_pathe(t_copy *copy_env, char *str)
{
	t_copy *curr;

	curr = copy_env;
	while (curr)
	{
		if (ft_strcmp(curr->key, str) == 0)
		{
			return (ft_strdup(curr->value));
		}
		curr = curr->next;
	}
	if (!ft_strcmp(str, "secret_pwd="))
	{
		while (curr)
		{
			if (ft_strcmp(curr->key, "secret_pwd=") == 0)
			{
				return (ft_strdup(curr->value));
			}
			curr = curr->next;
		}
	}
	return (NULL);
}

int handle_cd(char **argv, t_data *data)
{
	char *home = NULL;
	char *oldpwd = NULL;
	char cmd[PATH_MAX];
	char *pwd = NULL;
	char *new_pwd = NULL;
	char *tmp = NULL;
	(void)argv;

	if (getcwd(cmd, sizeof(cmd)))
		oldpwd = ft_strdup(cmd);
	else 
	{
		pwd = get_the_pathe(data->copy_env, "PWD=");
		if (pwd)
			oldpwd = ft_strdup(pwd);
	}
	if (!data->token->next || ft_strcmp(data->token->next->str, "~") == 0)
	{
		home = get_the_pathe(data->copy_env, "HOME=");
		if (!home || chdir(home) != 0)
		{
			ft_putstr_fd("minibash: ", STDERR_FILENO);
        	ft_putendl_fd_2(data->token->str, STDERR_FILENO);
			ft_putstr_fd(": HOME not set\n", STDERR_FILENO);
			return (1);
		}
	}
	else if (chdir(data->token->next->str) != 0)
	{
		if (errno == ENOENT)
		{
			ft_putstr_fd("minibash: ", STDERR_FILENO);
			ft_putendl_fd_2(data->token->str, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putendl_fd_2(data->token->next->str, STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		}
		else 
		{
			ft_putstr_fd("minibash: ", STDERR_FILENO);
			ft_putendl_fd_2(data->token->str, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putendl_fd_2(data->token->next->str, STDERR_FILENO);
			ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		}
		return (1);
	}
	if (getcwd(cmd, sizeof(cmd)))
		new_pwd = ft_strdup(cmd);
	else if (pwd)
	{
		ft_putendl_fd_2(data->token->str, STDERR_FILENO);
		ft_putstr_fd(": error retrieving current directory:", STDERR_FILENO);
		ft_putstr_fd(" getcwd: cannot access parent directories:", STDERR_FILENO);
		ft_putstr_fd(" No such file or directory\n", STDERR_FILENO);
		tmp = ft_strjoin(pwd, "/");
		new_pwd = ft_strjoin(tmp, data->token->next->str);
	}
	else
	{
		pwd = get_the_pathe(data->copy_env, "secret_pwd=");
		ft_putendl_fd_2(data->token->str, STDERR_FILENO);
		ft_putstr_fd(": error retrieving current directory:", STDERR_FILENO);
		ft_putstr_fd(" getcwd: cannot access parent directories:", STDERR_FILENO);
		ft_putstr_fd(" No such file or directory\n", STDERR_FILENO);
		tmp = ft_strjoin(pwd, "/");
		new_pwd = ft_strjoin(tmp, data->token->next->str);
	}
	if (oldpwd)
		update_env_value(data->copy_env, "OLDPWD=", oldpwd);
	if (new_pwd)
	{
		update_env_value(data->copy_env, "PWD=", new_pwd);
		update_env_value(data->copy_env, "secret_pwd=", new_pwd);
	}
	return (0);
}
