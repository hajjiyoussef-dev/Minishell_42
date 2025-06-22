/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_hndl_wild2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:28:14 by yhajji            #+#    #+#             */
/*   Updated: 2025/06/22 17:36:36 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

char	**help_expand(char **matching, int *size, char *file_name)
{
	matching = gc_realloc(matching, *size, *size + 2);
	matching[(*size)++] = ft_strdup(file_name);
	matching[*size] = NULL;
	return (matching);
}
