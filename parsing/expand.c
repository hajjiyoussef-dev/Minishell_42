#include "mini_shell.h"

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isalnum(char c)
{
	return (ft_isdigit(c) || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

char *get_varaible(char *str, int *i, t_copy *copy, int checker)
{
	char	*to_search = NULL;
	if (str && str[*i] == '?')
	{
		(*i)++;
		if (checker == 2)
			return (ft_strdup("2"));
		else if (checker == 127)
			return (ft_strdup("127"));
		return (ft_strdup(ft_itoa(checker)));
	}
	if (str && (ft_isdigit(str[*i]) || str[*i] == '$'))
	{
		(*i)++;
		return (ft_strdup(""));
	}
	while (str && str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
	{
		to_search = ft_joinchar(to_search, str[*i]);
		(*i)++;
	}
	return (get_str(to_search, copy));
}


char	*expnand_it(char *str, t_copy *copy, int checker)
{
	char	*res = NULL;
	int		i = 0;

	while (str[i])
	{
		if (str[i] == '$' && str[i+1])
		{
			i++;
			res = ft_strjoin(res, get_varaible(str, &i, copy, checker));
		}
		else
		{
			res = ft_joinchar(res, str[i]);
			i++;
		}
	}
	return (res);
}

void expandd(t_toke *head, t_copy *copy, int checker)
{
	t_toke *tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
		{
			tmp = tmp->next;
			if (!tmp)
				break ;
			if (!ft_strcmp(tmp->str, "$"))
				tmp->str = ft_strdup("");
		}
		else if ((tmp->type == WORD || tmp->type == DB_QT) && ft_strchr(tmp->str, '$'))
		{
			tmp->str = expnand_it(tmp->str, copy, checker);
		}
		tmp = tmp->next;
	}
}
