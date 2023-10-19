/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eminishell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:37:22 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/10/19 12:01:33 by nacho            ###   ########.fr       */
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

//		Funciones temporales para testeo en builtins.c

int		ft_builtins(t_mini *mini, char *prompt);

//      HAND CRAFTED FUNCTIONS -- BUILTINS

int		ft_builtin_check(t_exec *exec, char **env);
int		ft_cd(char **cmd_mtx);
int		ft_echo(char **cmd_mtx);
int		ft_env(char **env, char **cmd_mtx);
int		ft_exit(char **cmd_mtx);
int		ft_pwd(void);
int		ft_export(char **env);
int		ft_unset(t_prg *prg, char *str);

//		SOLO FTS

int		ft_preprocess_solo(t_mini *mini);
pid_t	*ft_exec_solo(char **env, t_exec *exec);
t_exec	*ft_init_exec(t_tokens *token, char **env);
void	ft_in_out_type(t_tokens *token, t_exec *exec);

//		PIPE FTS

int		ft_preprocess_pipe(t_mini *mini);
void	ft_exec_pipe(t_pipe *pipes, t_mini *mini);
t_pipe	*ft_pipe_init(int pipe_num);
void	ft_in_out_pipe(t_exec *exec, t_tokens *token);
void	ft_in_out_default(t_pipe *pipes, int pipe_num);

//		UTILS FTS

int		here_doc(char *limiter);
void	ft_error_cmd(char *str);
char	*ft_find_path(char **envp, char *cmd);
char	*ft_no_path(char *cmd, char **pos_paths);

//		FREE FTS

void	ft_free_pipes(t_pipe *pipes, int pipe_n);
void	ft_free_exec(t_exec *exec);

#endif