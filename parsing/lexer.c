/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:24:06 by hrami             #+#    #+#             */
/*   Updated: 2025/06/21 23:39:25 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

t_toke	*create_token(char *str, t_type type, char spc_aftr)
{
	t_toke	*new_toke;

	new_toke = gc_malloc(sizeof(t_toke), 1);
	if (!new_toke)
		return (NULL);
	if (type == WORD || type == DB_QT || type == SNL_QT)
		new_toke->str = str;
	else
		new_toke->str = ft_strdup(str);
	new_toke->type = type;
	if (spc_aftr == ' ')
		new_toke->space_after = 1;
	else
		new_toke->space_after = 0;
	new_toke->fd = -1;
	new_toke->next = NULL;
	return (new_toke);
}

void	add_token(t_toke **list, t_toke *new_token)
{
	t_toke	*tmp;

	if (!*list)
		*list = new_token;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_token;
		new_token->prev = tmp;
	}
}

char	*copy_word(char *line, int *i)
{
	int		start;
	int		j;
	char	*word;

	start = *i;
	while (line[*i])
	{
		if (line[*i] != ' ' && line[*i] != '>' && line[*i] != '|'
			&& line[*i] != '\'' && line[*i] != '<' && line[*i] != '\"')
			(*i)++;
		else
			break ;
	}
	word = gc_malloc((*i - start) + 1, 1);
	if (!word)
		return (NULL);
	j = 0;
	while (start < *i)
		word[j++] = line[start++];
	word[j] = '\0';
	return (word);
}

char	*copy_quoted_word(char *line, int *i)
{
	char	*result;
	int		start;
	char	quote;
	int		t;

	quote = line[*i];
	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	t = 0;
	result = gc_malloc((*i - start) + 1, 1);
	if (!result)
		return (NULL);
	while (t < (*i - start) && line[start + t])
	{
		result[t] = line[start + t];
		t++;
	}
	result[t] = '\0';
	return (result);
}

t_toke	*lexer(char *line)
{
	int		i;
	t_toke	*list;

	list = NULL;
	i = 0;
	while (line[i])
	{
		if (handle_space(line, &i))
			continue ;
		else if (handle_pipe(line, &i, &list))
			continue ;
		else if (line[i] == '\"' || line[i] == '\'')
		{
			if (handle_quotes(line, &i, &list))
				return (NULL);
			continue ;
		}
		else if (handle_redirections(line, &i, &list))
			continue ;
		else
			handle_word(line, &i, &list);
	}
	return (list);
}
