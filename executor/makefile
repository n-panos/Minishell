# PROG DEFINITION

NAME		= e_minishell
SRC			= exec/builtins.c exec/exec.c exec/exec_solo.c exec/exec_pipe.c \
				exec/exec_utils.c exec/exec_free.c
BSRC		= exec/builtins/pwd.c exec/builtins/echo.c exec/builtins/env.c \
				exec/builtins/export.c exec/builtins/cd.c exec/builtins/unset.c \
				exec/builtins/exit.c exec/builtins/b_utils.c

OBJS		= ${SRC:.c=.o} ${BSRC:.c=.o}
HEADER		= -Iheader
LIBS		= -Lheader/libft -lft
CC			= gcc
CFLAGS		= -Werror -Wall -Wextra
CPPFLAGS	= -I/Users/ipanos-o/.brew/opt/readline/include
LDFLAGS		= -L/Users/ipanos-o/.brew/opt/readline/lib
RM			= rm -rf

# COLOUR DEFINITION #
RED     := \033[0;31m
BLUE    := \033[0;34m
GREEN   := \033[1;32m
WHITE   := \033[0;37m
RESET   := \033[0m

# DEBUG DEFINITION

ifdef DEBUG
    CFLAGS += -g3 -fsanitize=address
else
    CFLAGS += -g
endif

# BUILDS

.c.o:		%.o : %.c
					@${CC} ${CFLAGS} ${CPPFLAGS} ${HEADER} -c $< -o $(<:.c=.o)

all:		${NAME}

${NAME}:	${OBJS}
					@echo "${GREEN}<---> Compiling Libft <--->${RESET}"
					@make -C header/libft
					@${CC} ${CFLAGS} -lreadline ${LDFLAGS} ${OBJS} ${LIBS} -o ${NAME}
					@echo "${GREEN}<---> Minishell executor Compiled! ⌐(ಠ۾ಠ)¬ <--->${RESET}"

clean:
					@${RM} ${OBJS}

fclean:		clean
					@make -C header/libft fclean
					@${RM} ${NAME}
					@echo "$(GREEN)<==========> ALL REMOVED <==========>${RESET}"

re:			fclean all

.PHONY: clean all fclean re