/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eminishell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:37:22 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/10/17 13:13:48 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EMINISHELL_H
# define EMINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>

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

typedef struct s_mini
{
	int			pipe_n;
	char		**env;
	t_tokens	*tk_lst;
}	t_mini;

typedef struct s_exec
{
	char	*path;
	char	**cmd_mtx;
	int		fd_in;
	int		fd_out;
}	t_exec;

typedef struct s_pipe
{
	t_exec	**cmd;
	int		**fd;
}	t_pipe;

typedef struct s_tokens
{
	char				*value;
	t_type				type;
	char				*tool;
	struct s_tokens		*next;
	struct s_tokens		*prev;
}	t_tokens;

//      HAND CRAFTED FUNCTIONS -- BUILTINS

int		ft_builtins(t_prg *prg, char *prompt);
int		ft_exec_cd(char **cmd_mtx);
int		ft_exec_echo(char **cmd_mtx);
int		ft_exec_env(char **env, char **cmd_mtx);
int		ft_exec_pwd(void);
int		ft_exec_export(char **env);
int		ft_exec_unset(t_prg *prg, char *str);

#endif