##	PROJECT
NAME	=	minishell

##	MAKEFILE VARS
include	./includes/make/vars.mk

##	C FILES
SRC_FILES	=	main.c startup.c parser.c tokenization.c shutdown.c execute.c pathing.c mario.c
BUILTIN_FILES =	builtins/cd.c builtins/echo.c builtins/env.c builtins/export.c builtins/export_print.c builtins/pwd.c builtins/unset.c builtins/exit.c builtins/builtin.c
SRC			=	${addprefix ./src/, ${SRC_FILES} ${BUILTIN_FILES}}
OBJ			=	${SRC:.c=.o}

##	BASIC RULES
${NAME}: init libft ${OBJ}
	${CC} ${CFLAGS} ${OBJ} ${INCLUDES} ${LIBRARIES} -o ${BIN_DIR}/${NAME}

all: ${NAME}

clean: libft_clean
	rm -f ${OBJ} ${OBJ}

fclean: clean libft_fclean
	rm -f ${BIN_DIR}${NAME} ${BIN_DIR}${NAME}_bonus

re: fclean all

%.o: %.c
	${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@

##	HELPER MAKEFILES
include	./includes/make/libs.mk
include	./includes/make/tests.mk

.PHONY: all clean fclean re bonus init \
	libft libft_clone libft_re libft_clean libft_fclean \
	norm run print_valgrind_results
