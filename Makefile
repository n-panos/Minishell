NAME		=	minishell
CC			=	gcc
CFLAGS		=	-g3 -Wall -Werror -Wextra
READLINE	=	-I/System/Volumes/Data/Users/$(USER)/.brew/Cellar/readline/8.2.1/include -L/Users/$(USER)/.brew/opt/readline/lib -lreadline
RM 			=	rm -rf

LIBFT		= 	parser/src/libft/libft.a

LIST		=	ft_add_back_token.c	ft_new_token.c ft_free_all_tokens.c

HERE		=	get_heredoc.c

MAIN		=	parser/src/main.c
PARSER		=	loop.c list.c mini.c exec.c
UTILS		=	input.c tokenizer_utils.c expander.c expander_utils.c inquote.c expander_utils2.c typed.c tokenizer.c free.c
ERROR		=	puterror.c

LIST_PATH	=	$(addprefix parser/src/list/, $(LIST))
PARSER_PATH	=	$(addprefix parser/src/parser/, $(PARSER))
UTILS_PATH	=	$(addprefix parser/src/utils/, $(UTILS))
HERE_PATH	=	$(addprefix parser/src/heredoc/, $(HERE))
ERROR_PATH	=	$(addprefix parser/src/error/, $(ERROR))

## EXECUTOR

EXEC		=	exec.c exec_solo.c exec_pipe.c exec_utils.c exec_free.c
BUILTINS	=	pwd.c echo.c env.c cd.c unset.c exit.c b_utils.c #export.c

EXECUTOR	=	$(addprefix executor/exec/, $(EXEC))
BUILTINS_PATH	=	$(addprefix executor/exec/builtins/, $(BUILTINS))

# COLOUR DEFINITION #
RED     := \033[0;31m
BLUE    := \033[0;34m
GREEN   := \033[1;32m
WHITE   := \033[0;37m
RESET   := \033[0m

OBJS		=	$(MAIN:.c=.o) $(PARSER_PATH:.c=.o) $(UTILS_PATH:.c=.o) $(ERROR_PATH:.c=.o) $(LIST_PATH:.c=.o) $(HERE_PATH:.c=.o) $(EXECUTOR:.c=.o) $(BUILTINS_PATH:.c=.o)

all: $(NAME)

# main/%.o: main/%.c
# 	@$(CC) $(CFLAGS) -c $< -o $@ 

.c.o:		%.o : %.c
					@${CC} ${CFLAGS} -c $< -o $(<:.c=.o)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(READLINE) $(LIBFT)
	@echo "${GREEN}<---> Minishell Compiled! ⌐(ಠ۾ಠ)¬ <--->${RESET}"

$(LIBFT):
	@make bonus --directory parser/src/libft

clean:
	@$(RM) $(OBJS)
	@make clean --directory parser/src/libft

fclean: clean
	@$(RM) $(NAME)
	@make fclean --directory parser/src/libft

re: fclean all

.PHONY: re fclean clean