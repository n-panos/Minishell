/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:25:43 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/12/15 17:50:42 by ediaz--c         ###   ########.fr       */
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
	char				**env;
	t_list				*tokenlst;
	int					index;
	int					start;
	int					end;
	int					status;
	int					error;
	int					quote;
	int					expander;
	int					not_increment;
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
	int		v2;
	int		pid;
}	t_truncate;

// UTILS
/* main_utils.c */
char	*ft_increment_shlvl(char **env);
/* input .c */
int		ft_check_input(char *input, int *status);
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
int		ft_tr_env(t_parser *tools, int index, int state);
int		ft_three_str(t_truncate *tr, t_parser *tools, int state);
/* expander.c */
int		ft_getpid(t_parser *tools, int index);
int		ft_expand_env(t_parser *tools, int index, int state);
int		ft_expander(t_parser *tools, int index, char **str_iter, int state);
int		ft_getstatus(t_parser *tools, int index);
/* inquote.c */
int		ft_in_quote(t_parser *tools, int index);
char	*ft_del_quote(char **str, int index);
/* expander_utils2.c */
int		ft_is_operator(t_parser *tools, int index);
int		ft_not_expand(t_parser *tools, int index);
char	*get_env(char *env, t_parser *tools, int *v2);
char	*ft_expand_multi(char **split);
/* tokenizer.c */
t_list	*get_token(t_parser *tools);

char	**ft_create_env(void);
#endif