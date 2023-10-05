/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:14:28 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/10/05 12:42:44 by ediaz--c         ###   ########.fr       */
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
# include "../libft/includes/libft.h"
# define PROMPT "\033[0;92mMinishell> \033[0m"
# define DELIMITERS	"<>|"
# include "parser.h"

typedef struct s_tools
{
	int	prueba;
}	t_tools;

/*
*	Estructura de tipos de nodos:
*	NODE_COMMAND			->	Nodo de comando (ls, echo, etc.)
*	NODE_ARGUMEN			->	Nodo de argumento (argumentos de comandos)
*	NODE_PIPE				->	Nodo de tubería (|)
*	NODE_REDIRECT_INPUT		->	Nodo de redirección de entrada (<)
*	NODE_REDIRECT_OUTPUT	->	Nodo de redirección de salida (>)
*	NODE_REDIRECT_APPEND	->	Nodo de redirección de salida (>>)
*	NODE_HEREDOC			->	Nodo de heredoc (<<)
*	NODE_DELIMITER			->	Nodo de delimitación del heredoc (EOF)
*/
typedef enum s_type
{
	NODE_COMMAND,
	NODE_ARGUMENT,
	NODE_PIPE,
	NODE_REDIRECT_INPUT,
	NODE_REDIRECT_OUTPUT,
	NODE_REDIRECT_APPEND,
	NODE_HEREDOC,
	NODE_DELIMITER
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
*	Funciones de lista doblemente enlazadas
*/
t_tokens	*ft_new_token(char	*value);
void		ft_add_back_token(t_tokens **list, t_tokens *new);

//ERROR
int			ft_parser_error(char *err, char c);

// PARSER
/**/
void		minishell_loop(t_parser *tools);
/**/
t_tokens	*create_list(t_parser *tools);
/* typed.c */
int			ft_is_command(t_tokens *token);
int			ft_is_op(t_tokens *token);
int			ft_is_delimiter(t_tokens *token);
int			ft_is_argument(t_tokens *token);
#endif