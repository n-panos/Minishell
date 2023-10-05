NAME		=	minishell
CC			=	gcc
CFLAGS		=	-g3 -Wall -Werror -Wextra
READLINE	=	-I/System/Volumes/Data/Users/ediaz--c/.brew/Cellar/readline/8.2.1/include -L/System/Volumes/Data/usr/local/Cellar/readline/8.2.1/lib -lreadline
RM 			=	rm -rf

LIBFT		=	src/libft/libft.a

LIST		=	ft_add_back_token.c	ft_new_token.c

MAIN		=	src/main.c
PARSER		=	loop.c list.c
EXEC		=
UTILS		=	input.c tokenizer_utils.c expander.c expander_utils.c inquote.c expander_utils2.c typed.c
ERROR		=	puterror.c

LIST_PATH	=	$(addprefix src/list/, $(LIST))
PARSER_PATH	=	$(addprefix src/parser/, $(PARSER))
UTILS_PATH	=	$(addprefix src/utils/, $(UTILS))
ERROR_PATH	=	$(addprefix src/error/, $(ERROR))

OBJS		=	$(MAIN:.c=.o) $(PARSER_PATH:.c=.o) $(UTILS_PATH:.c=.o) $(ERROR_PATH:.c=.o) $(LIST_PATH:.c=.o)

all: $(NAME)

# main/%.o: main/%.c
# 	@$(CC) $(CFLAGS) -c $< -o $@ 

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(READLINE) $(LIBFT)

$(LIBFT):
	@make bonus --directory src/libft

clean:
	@$(RM) $(OBJS)
	@make clean --directory src/libft

fclean: clean
	@$(RM) $(NAME)
	@make fclean --directory src/libft

re: fclean all

.PHONY: re fclean clean