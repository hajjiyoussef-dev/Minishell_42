/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 20:48:24 by yhajji            #+#    #+#             */
/*   Updated: 2025/05/02 05:25:06 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"


t_gc *g_gc = NULL;

// garbage collector work withe it !!!!

void *gc_malloc(size_t size)
{
    
    void *ptr = malloc(size);
    if (!ptr)
        return (NULL);
    t_gc *node = malloc(sizeof(t_gc));

    node->ptr = ptr;
    node->next = g_gc;
    g_gc = node;
    return(ptr);
}
// void for now !!!!
void free_gc_malloc(void)
{
    t_gc *tmp;

    while (g_gc)
    {
        tmp = g_gc;
        free(g_gc->ptr);
        g_gc = g_gc->next;
        free(tmp);
    }
}