NAME = minishell

SRC = lexer.c shell.c tools_0.c syntax.c expand.c tools_1.c

INC = mini_shell.h
OBJS = ${SRC:.c=.o}
CC = cc  -Wall -Werror -Wextra -g -fsanitize=address
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