/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eminishell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:37:22 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/05 11:44:57 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EMINISHELL_H
# define EMINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include "../../parser/src/libft/includes/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include "../../parser/includes/minishell.h"

// typedef enum s_type
// {
// 	COMMAND,
// 	ARGUMENT,
// 	PIPE,
// 	REDIRECT_INPUT,
// 	REDIRECT_OUTPUT,
// 	REDIRECT_APPEND,
// 	HEREDOC,
// 	DELIMITER
// }	t_type;

// typedef struct s_tokens
// {
// 	char				*value;
// 	t_type				type;
// 	char				*tool;
// 	struct s_tokens		*next;
// 	struct s_tokens		*prev;
// }	t_tokens;

// typedef struct s_mini
// {
// 	int			pipe_n;
// 	char		**env;
// 	t_tokens	*tk_lst;
// }	t_mini;

typedef struct s_exec
{
	char	*path;
	char	**cmd_mtx;
	int		fd_in;
	int		fd_out;
}	t_exec;

typedef struct s_pipes
{
	t_exec	*cmd1;
	t_exec	*cmd2;
	int		*fd;
}	t_pipes;

//		Funciones temporales para testeo en builtins.c

//int			ft_builtins(t_mini *mini, char *prompt);

//      HAND CRAFTED FUNCTIONS -- BUILTINS

int			ft_cd(char **cmd_mtx, char **env);
int			ft_echo(char **cmd_mtx);
int			ft_env(char **env, char **cmd_mtx);
int			ft_exit(char **cmd_mtx);
int			ft_export(t_mini *mini, char **cmd_mtx);
int			ft_pwd(char **cmd_mtx);
int			ft_unset(t_mini *mini, char **cmd_mtx);

//		BUILTINS UTILS

int			ft_search_c(char *str, char c);
int			*ft_add_used(int *prev_used, int new_used);
int			ft_check_list(int *list, int n);

//		EXECUTE

int			ft_builtin_check(t_exec *exec, t_mini *mini);
int			ft_no_cmd(t_mini *mini);
int			here_doc(char *limiter);

//		SOLO FTS

int			ft_preprocess_solo(t_mini *mini);
pid_t		ft_exec_solo(char **env, t_exec *exec);
void		ft_in_out_type(t_tokens *token, t_exec *exec);

//		PIPE FTS

int			ft_preprocess_pipe(t_mini *mini);
int			*ft_exec_two(t_mini *mini, t_tokens *tkn, int *in);
void		ft_pipe_exec(t_mini *mini, t_pipes *pipes);
t_pipes		*ft_config_pipe(t_tokens *tkn, char **env, int in);
t_tokens	*ft_return_pipe(t_tokens *tkn);

//		UTILS FTS

int			ft_error_cmd(char *str, int in, int out);
t_exec		*ft_init_exec(t_tokens *token, char **env, int in, int out);
t_exec		*ft_add_cmd(t_tokens *tkn, char **env, int in);
char		*ft_find_path(char **envp, char *cmd);
char		*ft_no_path(char *cmd, char **pos_paths);

void		ft_waiting(int n);
int			ft_check_out(t_tokens *tkn);
int			ft_check_in(t_tokens *tkn, int in);

//		FREE FTS

void		ft_free_pipes(t_pipes *pipes);
void		ft_free_exec(t_exec *exec);

#endif