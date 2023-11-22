/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eminishell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:37:22 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/22 11:59:10 by ipanos-o         ###   ########.fr       */
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

//					**BUILTINS**

//			UTILS

void		ft_change_env_var(t_mini *mini, char *arg);
char		*ft_add_to_env(char **env, char *add);
int			ft_var_exists(char *env, char *add, int flag);
int			ft_search_c(char *str, char c);

//			CD
int			ft_cd(t_exec *exec, t_mini *mini);
int			ft_cd_select(t_mini *mini, t_exec *exc);
int			ft_cd_standard_dir(char *dir);
int			ft_cd_env_var(char **env, char *str, int out_fd);
char		*ft_get_env_var(char **env, char *str);
void		ft_change_old_pwd(t_mini *mini, char *prev_dir);

//			ECHO

int			ft_echo(t_exec *exec, char *dir);
int			ft_echo_args(char *arg);
void		ft_echo_print(int f, int i, t_exec *exec, char *dir);

//			ENV

int			ft_env(t_mini *mini, t_exec *exec);
char		**ft_env_compare(char **cmd_mtx, char *env, int out_fd);
int			ft_env_args(t_exec *exec, t_mini *mini);
void		ft_env_print(char *str, int out_fd);

//			EXIT

int			ft_exit(t_mini *mini, t_exec *exec);
int			ft_exit_more_args(char *arg, int flag);
int			ft_status_return(char *arg);
char		*ft_get_shlvl(char **env, int flag);
void		ft_change_shlvl(t_mini *mini, int flag);

//			EXPORT

int			ft_export(t_mini *mini, t_exec *exec);
int			ft_export_more_args(t_mini *mini, char *cmd_mtx);
int			ft_print_export(t_mini *mini, int out_fd);

char		*ft_orden(char **env, int env_len, char *str_exp, int *used);
char		*ft_str_construct(int ref, char **env, char *str_exp);
int			*ft_add_used(int *prev_used, int new_used);
int			ft_check_ref(int *used, int i, int ref, char **env);
int			ft_check_list(int *list, int n);

//			PWD

int			ft_pwd(t_exec *exec);

//			UNSET

int			ft_unset(t_mini *mini, char **cmd_mtx);
int			ft_env_rm(t_mini *mini, char *str);
int			ft_env_delete(t_mini *mini, int erase);

//					FREE

void		ft_free_exec(t_mini *mini, t_exec *exec);

//					**EXECUTE**

int			ft_no_cmd(t_mini *mini);
int			ft_is_env_i_mini(t_mini *mini);
int			ft_cmp_mini(t_tokens *tkn);
t_exec		*ft_i_mini_util(t_mini *mini, t_tokens *tkn);

//			PIPE

int			ft_preprocess_pipe(t_mini *mini, int in);
int			ft_forking_pipe(t_mini *mini, t_exec *exec, int *fd, t_tokens *aux);
int			ft_pipe_no_child(t_mini *mini, t_exec *exec, int *fd);
void		ft_executing_pipe_cmds(t_exec *exec, int *fd, char **env);

t_tokens	*ft_return_pipe(t_tokens *tkn);
int			ft_is_exit(t_mini *mini, t_tokens *lst);

//			SOLO

int			ft_preprocess_solo(t_mini *mini);
int			ft_forking_solo(t_mini *mini, t_exec *exec);
int			ft_solo_no_child(t_mini *mini, t_exec *exec);
void		ft_executing_solo_cmds(char **env, t_exec *exec);
int			ft_is_minishell(t_mini *mini, t_exec *exec);
void		ft_minishell_exec(char **env, t_exec *exec);

//			EXEC-UTILS

void		ft_solo_wait(t_mini *mini);
void		ft_pipe_wait(t_mini *mini);
int			ft_wait_status(int i);
char		*ft_join_n(char *ret, char *add, char *s_add);
int			ft_error_cmd(t_mini *mini, char *str, int in, int out);

int			ft_builtin_check(t_exec *exec, t_mini *mini);
int			here_doc(char *limiter);

//			STRUCT-INITS

t_exec		*ft_add_cmd(t_tokens *tkn, t_mini *mini, int in);
t_exec		*ft_init_exec(t_tokens *token, t_mini *mini, int in, int out);
int			ft_builtin_path(char *cmd);

//					**FIND-PATH**

char		*ft_find_path(char **envp, char *cmd, int flag);
char		*ft_no_path(char *cmd, char **pos_paths);

//					**REDIRECT**

int			check_out(t_mini *mini, t_tokens *tkn);
int			check_in(t_mini *mini, t_tokens *tkn, int in);
int			ft_file_exists(t_mini *mini, char *file);

#endif