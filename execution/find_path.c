/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 02:27:34 by yhajji            #+#    #+#             */
/*   Updated: 2025/06/14 01:51:44 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini_shell.h"

char	*ft_get_argv_path_help(char *cmd, char **paths)
{
	int		i;
	char	*part_path;
	char	*real_path;

	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		real_path = ft_strjoin(part_path, cmd);
		if (access(real_path, X_OK) == 0)
		{
			return (real_path);
		}
		i++;
	}
	return (NULL);
}

char *find_path(char *argv, char **ev)
{
    int		i;
	char	**paths;
	char	*result;

	if (ft_str_chr(argv, '/'))
    {
        if (access(argv, X_OK) == 0)
            return (ft_strdup(argv));
        return (NULL);
    }
	i = 0;
	//|| ft_strnstr(ev[i],  "secret_PATH=", 12) == NULL
	while (ev[i] && (ft_strnstr(ev[i], "PATH=", 5) == NULL))
        i++;
	// if (!ev[i])
	// {
	// 	printf("zdjvbskdjbv\n");
	// 	while (ev[i] && (ft_strnstr(ev[i],  "secret_PATH=", 12) == NULL))
	// 		i++;
	// }
    if (!ev[i] || !argv || !argv[0])
		return (NULL);
	paths = ft_sp_lit(ev[i] + 5, ':');
	if (!paths)
	{
		perror("Error: in geting the pathe\n");
	}
	result = ft_get_argv_path_help(argv, paths);
	return (result);
}
