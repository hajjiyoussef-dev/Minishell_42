/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 02:28:34 by yhajji            #+#    #+#             */
/*   Updated: 2025/06/13 02:29:16 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini_shell.h"

char **build_argv(t_toke *cmd_start, t_toke *end_cmd, t_data *data)
{
    int argc = 0;
    t_toke *curr;
    char **argv;
    int i = 0;
    t_toke *prev = NULL;
    (void)data;
    
    curr = cmd_start;
    while (curr && curr != end_cmd->next)
    {
        if (curr->type == WORD || curr->type == DB_QT || curr->type == SNL_QT)
            argc++;
        if (curr->type == REDIR_IN || curr->type == REDIR_OUT ||
            curr->type == APPEND || curr->type == HEREDOC)
            curr = curr->next; 
        curr = curr->next;
    }
    argv = gc_malloc(sizeof(char *) *(argc + 1), 1);
    if (!argv)
    {
        perror("gc_malloc failed\n");
        gc_malloc(0, 0);
        exit(1);
    }
    curr = cmd_start;
    while (curr != NULL && (curr != end_cmd->next))
    {
        if ((curr->type == WORD || curr->type == DB_QT || curr->type == SNL_QT ) )
        {
            if (!prev || (prev->type != REDIR_IN && prev->type != REDIR_OUT &&
                prev->type != APPEND && prev->type != HEREDOC))
            {
                argv[i] = ft_strdup(curr->str);
                if (!argv[i])
                {
                    perror("ft_strdup failed\n");
                    gc_malloc(0, 0);
                    exit(1);
                }
                i++;
            }
        }
        if (curr->type == REDIR_OUT || curr->type == APPEND || curr->type == HEREDOC)
            curr = curr->next;
        prev = curr;
        if (curr)
            curr = curr->next;
    }
    argv[i] = NULL;
    return (argv);
}
