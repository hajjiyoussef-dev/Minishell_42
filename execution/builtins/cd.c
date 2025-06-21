/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:43:21 by yhajji            #+#    #+#             */
/*   Updated: 2025/06/20 10:43:33 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parsing/mini_shell.h"

char	*get_oldpwd(t_data *data)
{
	char	cmd[PATH_MAX];
	char	*pwd;

	if (getcwd(cmd, sizeof(cmd)))
		return (ft_strdup(cmd));
	pwd = get_the_pathe(data->copy_env, "PWD=");
	if (pwd)
		return (ft_strdup(pwd));
	return (NULL);
}

int	update_pwd_env(t_data *data, char *oldpwd)
{
	char	cmd[PATH_MAX];
	char	*new_pwd;
	char	*tmp;
	char	*pwd;

	if (getcwd(cmd, sizeof(cmd)))
		new_pwd = ft_strdup(cmd);
	else
	{
		pwd = get_the_pathe(data->copy_env, "PWD=");
		if (!pwd)
			pwd = get_the_pathe(data->copy_env, "secret_pwd=");
		print_getcwd_error(data->token->str);
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

static int	print_cd_error(char *cmd, char *target, char *msg)
{
	ft_putstr_fd("minibash: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	if (target)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(target, STDERR_FILENO);
	}
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	return (1);
}

static int	change_directory(t_data *data)
{
	char	*home;
	char	*target;

	if (!data->token->next || ft_strcmp(data->token->next->str, "~") == 0)
	{
		home = get_the_pathe(data->copy_env, "HOME=");
		if (!home || chdir(home) != 0)
			return (print_cd_error(data->token->str, NULL, "HOME not set"));
	}
	else
	{
		target = data->token->next->str;
		if (chdir(target) != 0)
		{
			if (errno == ENOENT)
				return (print_cd_error(data->token->str, target,
						"No such file or directory"));
			else
				return (print_cd_error(data->token->str, target,
						"Permission denied"));
		}
	}
	return (0);
}

int	handle_cd(char **argv, t_data *data)
{
	char	*oldpwd;

	(void)argv;
	oldpwd = get_oldpwd(data);
	if (change_directory(data) != 0)
		return (1);
	update_pwd_env(data, oldpwd);
	return (0);
}
