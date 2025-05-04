NAME = minishell

SRC = ./parsing/lexer.c ./parsing/shell.c  execution.c gc_malloc.c \
			execution_tools.c ft_split.c ft_strjoin.c ./parsing/syntax.c ./parsing/expand.c \
			parsing/tools_fun_1.c parsing/copy_env.c parsing/tools_fun_0.c \
			signal/signal.c

INC = ../test.h
OBJS = ${SRC:.c=.o}
CC = cc -Wall -Werror -Wextra #-fsanitize=address
RM = rm -f

all: ${NAME}
%.o: %.c ${INC}
	${CC} -c $< -o $@

${NAME}: ${OBJS}
	${CC} ${OBJS} -lreadline -o ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all