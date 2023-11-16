/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:14:28 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/11/16 14:12:27 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <termios.h>
# include <curses.h>
# define NOC "\001\e[0m\002"
# define PROMPT "\001\033[0;92m\002Minishell> \001\033[0m\002"
# define DELIMITERS	"<>|"
# include "parser.h"
# define OFF "\033[0m"
# define P "\033[1;95m"
# define Y "\033[1;5;93m"
# define R "\033[1;91m"

/*
*	0 -> Shell iteractiva
*	1 -> Shell en ejecucion
*/
int	g_signal;
# define ITERATIVE	1
# define PROCESS	2
# define HERE_DOC	3
# define PATH_VAR	"=/usr/local/bin:/System/Cryptexes/App/usr/bin:/usr/bin:/bin:/usr/sbin:/sbin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/local/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/appleinternal/bin:/Library/Apple/usr/bin"
// # include "../../executor/header/eminishell.h"

/*
*	Estructura de tipos de nodos:
*	COMMAND				->	Nodo de comando (ls, echo, etc.)
*	NODE_ARGUMEN		->	Nodo de argumento (argumentos de comandos)
*	PIPE				->	Nodo de tubería (|)
*	REDIRECT_INPUT		->	Nodo de redirección de entrada (<)
*	REDIRECT_OUTPUT		->	Nodo de redirección de salida (>)
*	REDIRECT_APPEND		->	Nodo de redirección de salida (>>)
*	HEREDOC				->	Nodo de heredoc (<<)
*	DELIMITER			->	Nodo de delimitación del heredoc (EOF)
*/
typedef enum s_type
{
	COMMAND,
	ARGUMENT,
	PIPE,
	REDIRECT_INPUT,
	REDIRECT_OUTPUT,
	REDIRECT_APPEND,
	HEREDOC,
	DELIMITER
}	t_type;

/*
*	Estructura de lista doblemente enlazadas de tokens
*/
typedef struct s_tokens
{
	char				*value;
	t_type				type;
	char				*tool;
	struct s_tokens		*next;
	struct s_tokens		*prev;
}	t_tokens;

/*
*	Estructura de herramientas de la minishell
*/
typedef struct s_mini
{
	t_tokens		*tk_lst;
	int				cmd_n;
	int				status;
	int				flag_path;
	char			**env;
	struct s_parser	*tools;
}	t_mini;

/*
*	Funciones de lista doblemente enlazadas
*/
t_tokens	*ft_new_token(char	*value);
void		ft_add_back_token(t_tokens **list, t_tokens *new);
void		ft_free_all_tokens(t_tokens **lst, void (*del)(void *));

//ERROR
int			ft_parser_error(char *err, char c);

// PARSER
/**/
int			minishell_loop(t_mini *mini);
/**/
t_tokens	*create_list(t_parser *tools);
/* mini.c */
void		ft_cmd_nmb(t_mini	*mini);

/* typed.c */
int			ft_is_command(t_tokens *token);
int			ft_is_op(t_tokens *token);
int			ft_is_delimiter(t_tokens *token);
int			ft_is_argument(t_tokens *token);
/* free.c */
void		ft_free_loop(t_parser *tools, t_mini *mini);
void		free_all(t_mini *mini);
// EXEC
int			ft_execute(t_mini *mini);

/* Pintar nodos */
void		print_lst_doble(t_tokens *lst);

/* SIGNALS */
void		child_signal(void);
void		signal_handler(int state);
void		show_ctl(int sig);
void		create_signal(struct sigaction *signal, void (*funct)(int));
void		ctrl(int sa);
void		signal_off(void);
#endif