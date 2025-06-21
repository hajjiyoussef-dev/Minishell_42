NAME = minishell

SRC = lexer.c shell.c tools_fun_0.c syntax.c expand.c tools_fun_1.c copy_env.c her_doc.c \
		rediraction.c  split_word.c ft_splite.c concatinate.c helpe_lexer.c herdoc_setup.c help_split_word.c \
		../execution/execution.c ../execution/gc_malloc.c  ../execution/execution_tools.c ../execution/ft_strjoin.c ../execution/signal/signal.c \
		../execution/builtins/env.c  ../execution/builtins/pwd.c ../execution/builtins/export.c \
		../execution/builtins/unset.c ../execution/builtins/cd.c ../execution/builtins/echo.c ../execution/builtins/exit.c \
		../execution/builtins/update_export.c ../execution/builtins/print_export.c ../execution/fd_traker.c ../execution/build_argv.c \
		../execution/env_list_to_array.c  ../execution/handel_builting_exe.c  ../execution/handle_redirections.c \
		../execution/find_path.c  handle_wildcards.c help_hndl_wild.c ../execution/builtins/help_cd.c ../execution/builtins/help_exit.c \
		../execution/help_execution_part1.c  ../execution/help_execution_part2.c ../execution/help_execution_part3.c  

INC = mini_shell.h
OBJS = ${SRC:.c=.o}
CC = cc  -Wall -Werror -Wextra   #-g -fsanitize=address
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