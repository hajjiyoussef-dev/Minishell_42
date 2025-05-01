/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:42:20 by yhajji            #+#    #+#             */
/*   Updated: 2025/05/01 20:43:26 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void execute_cmds(t_toke *tokens)
{
    t_toke *curr = tokens;
    int p_fds[2];
    pid_t pid;

    while (curr)
    {
        if (curr->type = PIPE)
        {
            if (pipe(p_fds) == -1)
                perror("pipe failed");
                exit(1);
        }
    }
    pid = fork();
    if (pid == 0)
    {
        
    }
    
    
}


int main(void)
{

    t_toke *heade;
    heade =  build_test_tokens();

    execute_cmds(&heade);
    
}   