/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eminishell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:37:22 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/10/04 09:20:39 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EMINISHELL_H
# define EMINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>

# define COMMAND			1
# define PIPE				2
# define ARGUMENT			3
# define REDIRECT_INPUT		4
# define REDIRECT_OUTPUT	5
# define HERE_DOC			6
# define DELIMITER			7

enum	node
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_ARGUMENT,
	NODE_REDIRECT_INPUT,
	NODE_REDIRECT_OUTPUT,
	NODE_REDIRECT_APPEND,
	NODE_HERE_DOC,
	NODE_DELIMITER
}	node_types;

typedef struct s_prg
{
	char	**env;
}			t_prg;

//      HAND CRAFTED FUNCTIONS -- BUILTINS

int		ft_builtins(t_prg *prg, char *prompt);
int		ft_exec_pwd(void);
int		ft_exec_echo(char *str);
int		ft_exec_env(char **env, int flag);
int		ft_exec_export(char **env);
int		ft_exec_cd(char *str);
int		ft_exec_unset(t_prg *prg, char *str);

#endif