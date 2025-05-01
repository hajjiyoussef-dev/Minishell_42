/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:40:26 by yhajji            #+#    #+#             */
/*   Updated: 2025/05/01 20:55:34 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H 
#define TEST_H


#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>



// for the execution 

typedef struct s_exec_cmd
{
	char **argv;
	char *infile;
	char *outfile ;
	int append;  // 1 if >> 0 if >
	int heredoc; 
} t_exec_cmd;

typedef struct s_gc {
    void            *ptr;
    struct s_gc     *next;
}   t_gc;

t_gc *g_gc = NULL;



// for the parsing 

typedef enum s_type
{
	PIPE,
	WORD,
	DB_QT,
	SNL_QT,
	APPEND,
	REDIR_OUT,
	HEREDOC,
	REDIR_IN
} t_type;



typedef struct s_toke
{
	char			*str;          // the actual string content (command, arg, or file name)
	t_type			type;          // the type of token
	int				space_after;   // 1 if there was a space after this token in input, 0 otherwise
	struct s_toke	*next;         // pointer to next token
} t_toke;

// for the test ::
t_toke *build_test_tokens(void);

#endif