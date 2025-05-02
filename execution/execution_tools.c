/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 04:35:06 by yhajji            #+#    #+#             */
/*   Updated: 2025/05/02 07:20:00 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"


char **copy_envp(char **envp)
{
	int i = 0;
	char **copy;

	while (envp[i])
		i++;
	copy = gc_malloc((i + 1) * sizeof(char *));
	if (!copy);
		return (NULL);
	i = 0;
	while (envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
	
	
}