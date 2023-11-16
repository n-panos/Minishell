/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eminishell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:37:22 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/16 13:28:50 by ipanos-o         ###   ########.fr       */
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

//					**BUILTINS**

//			UTILS

void		ft_change_env_var(t_mini *mini, char *arg);
char		*ft_add_to_env(char **env, char *add);
int			ft_var_exists(char *env, char *add, int flag);
int			ft_search_c(char *str, char c);

//			CD
int			ft_cd(char **cmd_mtx, t_mini *mini);
char		*ft_get_env_var(char **env, char *str);
int			ft_cd_standard_dir(char *dir);
int			ft_cd_env_var(char **env, char *str);
void		ft_change_old_pwd(t_mini *mini, char *prev_dir);

//			ECHO

int			ft_echo(t_exec *exec, char *dir);
int			ft_echo_args(char *arg);
void		ft_echo_print(int f, int i, t_exec *exec, char *dir);

//			ENV

int			ft_env(char **env, char **cmd_mtx);
char		**ft_env_compare(char **cmd_mtx, char *env);
int			ft_env_args(char **cmd);

//			EXIT

int			ft_exit(t_mini *mini, char **cmd_mtx);
int			ft_exit_more_args(char *arg, int flag);
int			ft_status_return(char *arg);
void		ft_change_shlvl(t_mini *mini, int flag);

//			EXPORT

int			ft_export(t_mini *mini, char **cmd_mtx);
int			ft_export_more_args(t_mini *mini, char *cmd_mtx);
char		*ft_orden(char **env, int env_len, char *str_exp, int *used);
char		*ft_str_construct(int ref, char **env, char *str_exp);
int			*ft_add_used(int *prev_used, int new_used);
int			ft_check_ref(int *used, int i, int ref, char **env);
int			ft_check_list(int *list, int n);

//			PWD

int			ft_pwd(char **cmd_mtx);

//			UNSET

int			ft_unset(t_mini *mini, char **cmd_mtx);
int			ft_env_rm(t_mini *mini, char *str);
int			ft_env_delete(t_mini *mini, int erase);

//					FREE

void		ft_free_pipes(t_pipes *pipes);
void		ft_free_exec(t_exec *exec);

//					**EXECUTE**

//			PIPE

int			ft_preprocess_pipe(t_mini *mini);
int			*ft_exec_two(t_mini *mini, t_tokens *tkn, int *in);
int			ft_pipe_exec(t_mini *mini, t_pipes *pipes, int *fd);
t_pipes		*ft_config_pipe(t_tokens *tkn, t_mini *mini, int in);
t_tokens	*ft_return_pipe(t_tokens *tkn);

//			SOLO

int			ft_preprocess_solo(t_mini *mini);

//			EXEC-UTILS

t_exec		*ft_add_cmd(t_tokens *tkn, t_mini *mini, int in);
t_exec		*ft_init_exec(t_tokens *token, char **env, int in, int out);
int			ft_exec_type(t_mini *mini, t_exec *exec, int in, int out);
void		ft_exec_solo(char **env, t_exec *exec);
int			ft_is_minishell(t_mini *mini, t_exec *exec);

void		ft_waiting(t_mini *mini, int *fd);
char		*ft_join_n(char *ret, char *add, char *s_add);
int			ft_error_cmd(t_mini *mini, char *str, int in, int out);
char		*ft_get_shlvl(char **env, int flag);
void		ft_pipe_odd(t_mini *mini, t_tokens *atkn, int aux_fd);

int			ft_builtin_check(t_exec *exec, t_mini *mini);
int			ft_no_cmd(t_mini *mini);
int			here_doc(char *limiter);

//					**FIND-PATH**

char		*ft_find_path(char **envp, char *cmd);
char		*ft_no_path(char *cmd, char **pos_paths);

//					**REDIRECT**

int			check_out(t_mini *mini, t_tokens *tkn);
int			check_in(t_mini *mini, t_tokens *tkn, int in);

#endif