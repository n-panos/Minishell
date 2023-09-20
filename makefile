# PROG DEFINITION

NAME		= e_minishell
SRC			= src/main.c
BSRC		= src/hc_fts/pwd.c src/hc_fts/echo.c src/hc_fts/env.c src/hc_fts/export.c

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