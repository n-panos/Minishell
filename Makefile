NAME			=	minishell
CC				=	gcc
RM 				=	rm -rf

INCLUDES 		=	$(READLINE_INC)
LIBRARIES		=	$(READLINE_LIB)

CFLAGS			=	-Wall -Werror -Wextra $(INCLUDES) $(MAKEDEPENDS)
LDFLAGS 		= 	$(LIBRARIES)
MAKEDEPENDS		=	-MMD
DEBUG			=	-ggdb -g3
SANITIZE		=	-fsanitize=address

READLINE_LIB	=	-L /Users/$(USER)/.brew/opt/readline/lib -l readline
READLINE_INC 	=	-I /Users/$(USER)/.brew/opt/readline/include/
LIBFT			= 	-L parser/src/libft -l ft

LIST			=	ft_add_back_token.c	ft_new_token.c ft_free_all_tokens.c
LIST_PATH		=	$(addprefix parser/src/list/, $(LIST))
SRCS			+=	$(LIST_PATH)

MAIN			=	main.c
MAIN_PATH		=	$(addprefix parser/src/, $(MAIN))
SRCS			+=	$(MAIN_PATH)

PARSER			=	loop.c list.c mini.c
PARSER_PATH		=	$(addprefix parser/src/parser/, $(PARSER))
SRCS			+=	$(PARSER_PATH)

UTILS			=	input.c tokenizer_utils.c expander.c expander_utils.c inquote.c expander_utils2.c typed.c tokenizer.c free.c env_create.c expander_env_utils.c
UTILS_PATH		=	$(addprefix parser/src/utils/, $(UTILS))
SRCS			+=	$(UTILS_PATH)

ERROR			=	puterror.c
ERROR_PATH		=	$(addprefix parser/src/error/, $(ERROR))
SRCS			+=	$(ERROR_PATH)

## SIGNALS

SIGNAL			=	signal_handler.c signal_functions.c
SIGNAL_PATH		=	$(addprefix signal/, $(SIGNAL))
SRCS			+=	$(SIGNAL_PATH)

## EXECUTOR

EXEC			=	exec.c exec_solo.c pipes.c pipes_utils.c exec_utils.c find_path.c exec_free.c exec_utils_more.c struc_ex_inits.c
EXEC_PATH		=	$(addprefix executor/exec/, $(EXEC))
SRCS			+=	$(EXEC_PATH)

BUILTINS		=	pwd.c echo.c env.c cd.c unset.c exit.c b_utils.c export.c export_utils.c
BUILTINS_PATH	=	$(addprefix executor/exec/builtins/, $(BUILTINS))
SRCS			+=	$(BUILTINS_PATH)

## REDIRECT

REDIRECT		=	redirect.c
REDIRECT_PATH	=	$(addprefix redirect/, $(REDIRECT))
SRCS			+=	$(REDIRECT_PATH)

# COLOUR DEFINITION #
RED     := \033[0;31m
BLUE    := \033[0;34m
GREEN   := \033[1;32m
WHITE   := \033[0;37m
RESET   := \033[0m

OBJS 			=	$(SRCS:.c=.o)
DEPS			=	$(SRCS:.c=.d)

all: $(NAME)

# main/%.o: main/%.c
# 	@$(CC) $(CFLAGS) -c $< -o $@ 

.c.o:		%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(LDFLAGS) $^ -o $@
	@echo "$(GREEN)<---> Minishell Compiled! ⌐(ಠ۾ಠ)¬ <--->$(RESET)"

$(LIBFT):
	@make bonus --directory parser/src/libft

print:
	echo $(OBJS)
	echo $(SRCS)

debug: CFLAGS 			+= 	$(DEBUG) $(SANITIZE)
debug: LDFLAGS			+=	$(SANITIZE)
debug: re

erick: READLINE_LIB		=	-L/usr/local/opt/readline/lib -lreadline
erick: READLINE_INC		=	-I/usr/local/opt/readline/include/
erick: all

nacho: READLINE_LIB		=	-L/usr/local/opt/readline/lib -lreadline
nacho: READLINE_INC		=	-I/usr/local/opt/readline/include/
nacho: debug

clean:
	@$(RM) $(OBJS) $(DEPS)
	@make clean --directory parser/src/libft

fclean: clean
	@$(RM) $(NAME)
	@make fclean --directory parser/src/libft

re: fclean all

-include		$(DEPS)

.SILENT:	print
.PHONY: re fclean clean