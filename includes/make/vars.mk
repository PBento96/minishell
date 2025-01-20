##	COMPILER
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
CFLAGS_DEBUG	=	${CFLAGS} -g

##	ARGS
ARGS			?=

##	FOLDERS
INCLUDES_DIR	=	./includes
LIBFT_DIR		=	${INCLUDES_DIR}/libft
BIN_DIR			=	./bin
LOGS_DIR		=	./logs
NORM_DIRS		=	${LIBFT_DIR} ${INCLUDES_DIR}/minishell.h ./src

##	LIBRARIES
INCLUDES = -I ${INCLUDES_DIR}
LIBRARIES = ${LIBFT_DIR}/libft.a

##	GIT
LIBFT_REPO = git@github.com:PBento96/libft.git

##	TESTERS
VALGRIND		=	valgrind --leak-check=full --show-leak-kinds=all -s \
	--track-origins=yes --trace-children=yes --error-limit=no --track-fds=yes
VALGRIND_LOGS	=	--log-file=${BIN_DIR}/valgrind.log
GDB				=	gdb
NORM_LOGS		=	${LOGS_DIR}/norm.log

##	ANSI CODES
C_BLACK			=	\033[30m
C_RED			=	\033[31m
C_GREEN			=	\033[32m
C_YELLOW		=	\033[33m
C_BLUE			=	\033[34m
C_MAGENTA		=	\033[35m
C_CYAN			=	\033[36m
C_WHITE			=	\033[37m
C_BRT_BLACK		=	\033[90m
C_BRT_RED		=	\033[91m
C_BRT_GREEN		=	\033[92m
C_BRT_YELLOW	=	\033[93m
C_BRT_BLUE		=	\033[94m
C_BRT_MAGENTA	=	\033[95m
C_BRT_CYAN		=	\033[96m
C_BRT_WHITE		=	\033[97m

BG_BLACK		=	\033[40m
BG_RED			=	\033[41m
BG_GREEN		=	\033[42m
BG_YELLOW		=	\033[43m
BG_BLUE			=	\033[44m
BG_MAGENTA		=	\033[45m
BG_CYAN			=	\033[46m
BG_WHITE		=	\033[47m
BG_BRT_BLACK	=	\033[100m
BG_BRT_RED		=	\033[101m
BG_BRT_GREEN	=	\033[102m
BG_BRT_YELLOW	=	\033[103m
BG_BRT_BLUE		=	\033[104m
BG_BRT_MAGENTA	=	\033[105m
BG_BRT_CYAN		=	\033[106m
BG_BRT_WHITE	=	\033[107m

T_BOLD			=	\033[1m
T_DIM			=	\033[2m
T_ITALIC		=	\033[3m
T_UNDER			=	\033[4m
T_BLINK			=	\033[5m
T_REVERSE		=	\033[7m
T_HIDDEN		=	\033[8m
T_STRIKE		=	\033[9m

RESET_ALL		=	\033[0m
RESET_COLOR		=	\033[39m
RESET_BG		=	\033[49m
RESET_BOLD		=	\033[21m
RESET_DIM		=	\033[22m
RESET_ITALIC	=	\033[23m
RESET_UNDER		=	\033[24m
RESET_BLINK		=	\033[25m
RESET_REVERSE	=	\033[27m
RESET_HIDDEN	=	\033[28m
RESET_STRIKE	=	\033[29m
