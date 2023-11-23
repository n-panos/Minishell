/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_solo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:56:23 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/23 13:58:21 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/eminishell.h"

int	ft_preprocess_solo(t_mini *mini)
{
	int		ret;
	t_exec	*exec;

	ret = 0;
	exec = ft_add_cmd(mini->tk_lst, mini, 0);
	if (exec->cmd_mtx[0] && ft_strncmp(exec->cmd_mtx[0], "exit", 4) == 0)
		return (ft_exit(mini, exec));
	if (exec)
		ret = ft_forking_solo(mini, exec);
	signal_handler(ITERATIVE);
	return (ret);
}

int	ft_forking_solo(t_mini *mini, t_exec *exec)
{
	pid_t	pidc;

	if (g_signal != 1)
	{
		if (ft_solo_no_child(mini, exec) != 2)
			return (0);
		pidc = fork();
		child_signal();
		if (pidc == -1)
			exit(EXIT_FAILURE);
		if (pidc == 0)
			ft_executing_solo_cmds(mini->env, exec);
		mini->status = 0;
	}
	ft_free_exec(mini, exec);
	ft_solo_wait(mini);
	return (0);
}

int	ft_solo_no_child(t_mini *mini, t_exec *exec)
{
	int		i;

	if (exec->fd_in <= -1 || exec->fd_out <= -1)
		return (ft_free_exec(mini, exec), 0);
	i = ft_builtin_check(exec, mini);
	if (i == 2)
		i = ft_is_minishell(mini, exec);
	if (i == 2 && exec->path == NULL)
		i = ft_error_cmd(mini, exec->cmd_mtx[0], exec->fd_in, exec->fd_out);
	else
		mini->status = 0;
	if (i != 2)
		ft_free_exec(mini, exec);
	return (i);
}

void	ft_executing_solo_cmds(char **env, t_exec *exec)
{
	if (exec->fd_in > 0)
	{
		dup2(exec->fd_in, 0);
		close(exec->fd_in);
	}
	if (exec->fd_out > 1)
	{
		dup2(exec->fd_out, 1);
		close(exec->fd_out);
	}
	execve(exec->path, exec->cmd_mtx, env);
	printf("minishell: %s: Permission denied\n", exec->cmd_mtx[0]);
	exit(EXIT_FAILURE);
}

int	ft_is_minishell(t_mini *mini, t_exec *exec)
{
	char	str[FILENAME_MAX];
	// char	*prev_shlvl;
	int		status;

	if (!exec->cmd_mtx[0] || ft_strncmp(exec->cmd_mtx[0], "./minishell", 11) \
	!= 0 || ft_strlen(exec->cmd_mtx[0]) != 11)
		return (2);
	// prev_shlvl = ft_strjoin("SHLVL", ft_get_env_var(mini->env, "SHLVL"));
	// ft_change_shlvl(mini, 1);
	free(exec->path);
	getcwd(str, sizeof(str));
	exec->path = ft_strjoin(str, "/minishell");
	signal_off();
	ft_minishell_exec(mini->env, exec);
	wait(&status);
	mini->status = ft_wait_status(status);
	// ft_change_env_var(mini, prev_shlvl);
	// free(prev_shlvl);
	return (0);
}

void	ft_minishell_exec(char **env, t_exec *exec)
{
	pid_t	pidc;

	pidc = fork();
	if (pidc == -1)
		exit(EXIT_FAILURE);
	if (pidc == 0)
		ft_executing_solo_cmds(env, exec);
}