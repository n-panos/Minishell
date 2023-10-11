/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erick <erick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:25:43 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/10/11 11:27:19 by erick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "../src/libft/includes/libft.h"
/*
*	Estructura con variables utiles
*/
typedef struct s_parser
{
	char				*input;
	char				**envp;
	t_list				*tokenlst;
	int					index;
	int					start;
	int					end;
	int					status;
	int					error;
}	t_parser;
/*
*	PARSER
*	Estructura con variables
*/
typedef struct s_inQuote
{
	int		start;
	int		len;
	char	*inputcpy;
	char	quote_char;
}	t_inQuote;

/*
*	Estructura para romper y crear strigns
*/
typedef struct s_truncate
{
	char	*result;
	char	*tmp;
	char	*str1;
	char	*str2;
	char	*var1;
	char	*var2;
	int		pid;
}	t_truncate;

// UTILS
/* input .c */
int		ft_check_input(char *input);
int		find_quote_close(char *input, int index, char quote_char);
/* tokenizer_utils.c */
int		ft_space_char(t_parser *tools, int index);
int		ft_delimiters(t_parser *tools, int index);
int		ft_in_quote(t_parser *tools, int index);
int		ft_arguments(t_parser *tools, int index);
t_list	*create_token(t_parser *tools, int index);
int		ft_is_empty(char *str);
/* expander_utils.c */
char	*ft_get_env(char *str, int index);
char	*ft_createpid(char *str, int index);
void	ft_free_tr(t_truncate *tr);
int		ft_tr_status(t_parser *tools, int index);
int		ft_tr_env(t_parser *tools, int index);
/* expander.c */
int		ft_getpid(t_parser *tools, int index);
int		ft_expand_env(t_parser *tools, int index);
int		ft_expander(t_parser *tools, int index);
int		ft_getstatus(t_parser *tools, int index);
/* inquote.c */
int		ft_in_quote(t_parser *tools, int index);
/* expander_utils2.c */
int		ft_is_operator(t_parser *tools, int index);
int		ft_not_expand(t_parser *tools, int index);
/* tokenizer.c */
t_list	*get_token(t_parser *tools);
t_list	*create_token(t_parser *tools, int index);
int		ft_check_nodes(t_parser *tools);
#endif