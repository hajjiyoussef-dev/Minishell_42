/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrami <hrami@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 20:48:24 by yhajji            #+#    #+#             */
/*   Updated: 2025/05/26 22:36:27 by hrami            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini_shell.h"

t_gc    *new_node_ma(void *ptr)
{
    t_gc *new;

    new = malloc(sizeof(t_gc));
    if (!new)
        return (NULL);
    new->ptr = ptr;
    new->next = NULL;
    return (new);
}

void add_back_ma(t_gc **list, t_gc *new)
{
	t_gc *tmp;

	if (*list == NULL)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void gc_free_all(t_gc	**mlc)
{
    t_gc *tmp;
    while (*mlc)
    {
        tmp = (*mlc)->next;
        free((*mlc)->ptr);
        free(*mlc);
        *mlc= tmp;
    }
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	value;

	i = 0;
	p = (unsigned char *)b;
	value = (unsigned char)c;
	while (i < len)
	{
		p[i] = value;
		i++;
	}
	return (b);
}

void	*gc_malloc(size_t size, int flag)
{
	static t_gc	*mlc;
	t_gc			*new;
	void			*ptr;

	if (flag == 1)
	{
		ptr = malloc(size);
		if (!ptr)
			return (gc_free_all(&mlc), printf("malloc failed\n"), exit(1), NULL);
		ft_memset(ptr, 0, size);
		new = new_node_ma(ptr);
		if (!new)
			return (gc_free_all(&mlc), free(ptr), printf("malloc failed\n"), exit(1), NULL);
		add_back_ma(&mlc, new);
		return (ptr);
	}
	else if (flag == 0)
		gc_free_all(&mlc);
	return (NULL);
}
