NAME = minishell

SRC = lexer.c shell.c tools_fun_0.c syntax.c expand.c tools_fun_1.c copy_env.c \
		rediraction.c  split_word.c ft_splite.c \
		../execution/execution.c ../execution/gc_malloc.c  ../execution/execution_tools.c ../execution/ft_strjoin.c ../execution/signal/signal.c \
		../execution/ft_sp_lit.c ../execution/builtins/env.c  ../execution/builtins/pwd.c ../execution/builtins/export.c \
		../execution/builtins/unset.c ../execution/builtins/cd.c

INC = mini_shell.h
OBJS = ${SRC:.c=.o}
CC = cc  -Wall -Werror -Wextra #-g -fsanitize=address
RM = rm -f

all:  ${NAME}

%.o: %.c ${INC}
	${CC} -c $< -o $@

${NAME}: ${OBJS}
	${CC} ${OBJS}  -lreadline -o ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all