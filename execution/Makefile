NAME = libexecution.a

SRC =    execution.c gc_malloc.c  execution_tools.c ft_sp_lit.c ft_strjoin.c signal/signal.c

INC = mini_shell.h
OBJS = ${SRC:.c=.o}
CC = cc -Wall -Werror -Wextra #-fsanitize=address
RM = rm -f

all: ${NAME} 
%.o: %.c ${INC}
	${CC} -c $< -o $@

${NAME}: ${OBJS}
	${CC} ${OBJS} -o ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all