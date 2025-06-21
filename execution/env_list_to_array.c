/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_to_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 02:26:53 by yhajji            #+#    #+#             */
/*   Updated: 2025/06/21 23:41:46 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

char	**env_list_to_array(t_copy *copy_envp)
{
	t_copy	*tmp;
	int		count;
	char	**envp_array;
	int		i;
	char	*joined;

	(1) && (tmp = copy_envp, i = 0, count = 0);
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	envp_array = gc_malloc((sizeof(char *) * (count + 1)), 1);
	if (!envp_array)
		return (NULL);
	tmp = copy_envp;
	while (i < count)
	{
		joined = ft_str_join(tmp->key, tmp->value);
		envp_array[i] = joined;
		tmp = tmp->next;
		i++;
	}
	envp_array[i] = NULL;
	return (envp_array);
}
