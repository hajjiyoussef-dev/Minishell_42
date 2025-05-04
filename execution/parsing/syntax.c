#include "../mini_shell.h"

int	print_error(const char *msg)
{
	printf("minishell: syntax error near unexpected token `%s'\n", msg);
	return (2);
}

int is_redrict(t_type type)
{
    if (type == APPEND || type == REDIR_OUT
        || type == HEREDOC || type == REDIR_IN)
        return (1);
    return (0);
}

int	check_syntax(t_toke *tokens)
{
	t_toke *cur = tokens;
	if (!cur)
		return (0);

	if (cur->type == PIPE)
		return (print_error("|"));
	while (cur)
	{
		if (cur->type == PIPE && (!cur->next || cur->next->type == PIPE))
			return (print_error("|"));
        if (is_redrict(cur->type) && (!cur->next || cur->next->type != WORD))
		{
			if (!cur->next)
				return (print_error("newline"));
			return (print_error(cur->next->str));
		}
		cur = cur->next;
	}
	return (0);
}
