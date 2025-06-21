/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpe_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:26:55 by hrami             #+#    #+#             */
/*   Updated: 2025/06/21 23:39:40 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	handle_space(char *line, int *i)
{
	if (line[*i] == ' ' || (line[*i] <= 13 && line[*i] >= 9))
	{
		(*i)++;
		return (1);
	}
	return (0);
}

int	handle_pipe(char *line, int *i, t_toke **list)
{
	if (line[*i] == '|')
	{
		add_token(list, create_token("|", PIPE, line[*i + 1]));
		(*i)++;
		return (1);
	}
	return (0);
}

int	handle_quotes(char *line, int *i, t_toke **list)
{
	char	tmp;
	char	*word;

	if (line[*i] == '\'' || line[*i] == '\"')
	{
		tmp = line[*i];
		word = copy_quoted_word(line, i);
		if (line[*i] == tmp)
			(*i)++;
		else
			return (printf("minishell: syntax error you need close QT\n"), 1);
		if (tmp == '\"')
			add_token(list, create_token(word, DB_QT, line[*i]));
		else
			add_token(list, create_token(word, SNL_QT, line[*i]));
	}
	return (0);
}

int	handle_redirections(char *line, int *i, t_toke **list)
{
	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		add_token(list, create_token(">>", APPEND, line[*i + 2]));
		*i += 2;
		return (1);
	}
	else if (line[*i] == '>')
	{
		add_token(list, create_token(">", REDIR_OUT, line[*i + 1]));
		(*i)++;
		return (1);
	}
	else if (line[*i] == '<' && line[*i + 1] == '<')
	{
		add_token(list, create_token("<<", HEREDOC, line[*i + 2]));
		*i += 2;
		return (1);
	}
	else if (line[*i] == '<')
	{
		add_token(list, create_token("<", REDIR_IN, line[*i + 1]));
		(*i)++;
		return (1);
	}
	return (0);
}

void	handle_word(char *line, int *i, t_toke **list)
{
	char	*word;

	word = copy_word(line, i);
	add_token(list, create_token(word, WORD, line[*i]));
}
