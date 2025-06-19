/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_builting_exe.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 02:09:08 by yhajji            #+#    #+#             */
/*   Updated: 2025/06/19 17:57:16 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini_shell.h"


int is_single_builtin_cmd(t_toke *start, t_toke *end)
{
    
    t_toke *curr = start;
    while (curr && curr != end->next)
    {
        if (curr->type == PIPE)
            return 0;
        curr = curr->next;
    }
    
    if (start && is_cmd_buitin(start->str) &&
        (ft_strcmp(start->str, "cd") == 0 ||
         ft_strcmp(start->str, "export") == 0 ||
         ft_strcmp(start->str, "unset") == 0 ||
         ft_strcmp(start->str, "exit") == 0))
        return 1;
    return 0;
}

int execute_builtin(char **argv, t_data *data, t_toke *start)
{
    if (ft_strcmp(argv[0], "env") == 0)
    {
        handle_env(data);
        return (0);
    }
    else if (ft_strcmp(argv[0], "unset") == 0) 
        return (handle_unset(data->token, &data->copy_env));
    else if (ft_strcmp(argv[0], "pwd") == 0)
        return (handle_pwd(data)); 
    else if (ft_strcmp(argv[0], "export") == 0)
       return(handle_export(data));
    else if (ft_strcmp(argv[0], "cd") == 0)
        return (handle_cd(argv, data));
    else if (ft_strcmp(argv[0], "echo") == 0)
        return (handle_echo(start));
    else if (ft_strcmp(argv[0], "exit") == 0)
        return(handle_exit(data->token, start, data));
    return (0);
}
bool is_cmd_buitin(char *argv)
{
    static char *buiti[] = {"env", "unset", "export", "pwd", "cd", "echo", "exit",  NULL};
    int i;

    i = 0;
    while (buiti[i] != NULL)
    {
         if (ft_strcmp(argv, buiti[i]) == 0)
            return (true);   
        i++;
    }
    return (false);
}






