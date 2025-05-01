

#include "test.h"


t_toke *new_token(char *str, t_type type, int space_after)
{
	t_toke *token = malloc(sizeof(t_toke));
	token->str = strdup(str);
	token->type = type;
	token->space_after = space_after;
	token->next = NULL;
	return token;
}


t_toke *build_test_tokens(void)
{
	t_toke *t1 = new_token("ls", WORD, 1);
	t_toke *t2 = new_token("-l", WORD, 1);
	t_toke *t3 = new_token("|", PIPE, 1); // or just use type PIPE and str NULL
	t_toke *t4 = new_token("grep", WORD, 1);
	t_toke *t5 = new_token("minishell", WORD, 0);

	t1->next = t2;
	t2->next = t3;
	t3->next = t4;
	t4->next = t5;
	return t1;
}
