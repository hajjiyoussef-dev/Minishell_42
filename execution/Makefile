NAME = minishell

SRC = ./parsing/lexer.c ./parsing/shell.c ./parsing/tools.c execution.c gc_malloc.c \
			execution_tools.c ft_split.c ft_strjoin.c

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