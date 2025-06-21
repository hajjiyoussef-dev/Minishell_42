/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhajji <yhajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:44:21 by hrami             #+#    #+#             */
/*   Updated: 2025/06/21 23:39:09 by yhajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	print_error(const char *msg)
{
	printf("minishell: syntax error near unexpected token `%s'\n", msg);
	return (2);
}

int	is_redrict(t_type type)
{
	if (type == APPEND || type == REDIR_OUT
		|| type == HEREDOC || type == REDIR_IN)
		return (1);
	return (0);
}

int	is_valid_file_token(t_type type)
{
	if (type == WORD || type == DB_QT || type == SNL_QT)
		return (1);
	return (0);
}

int	check_syntax(t_toke *tokens)
{
	t_toke	*cur;

	cur = tokens;
	if (!cur)
		return (0);
	if (cur->type == PIPE)
		return (print_error("|"));
	while (cur)
	{
		if (cur->type == PIPE && (!cur->next || cur->next->type == PIPE))
			return (print_error("|"));
		if (is_redrict(cur->type) && (!cur->next
				|| !is_valid_file_token(cur->next->type)))
		{
			if (!cur->next)
				return (print_error("newline"));
			return (print_error(cur->next->str));
		}
		cur = cur->next;
	}
	return (0);
}

int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}
