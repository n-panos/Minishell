/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:16:49 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/15 17:10:44 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/eminishell.h"

// return es -1 si hubo algun error de ejecucion, 0 si ejecuto bien, 
// 1 si viene del comando exit y hay que cerrar la consola

int	ft_execute(t_mini *mini)
{
	int			ret;

	ret = 0;
	mini->status = 0;
	if (mini->cmd_n == 0)
		ret = ft_no_cmd(mini);
	if (mini->cmd_n == 1)
		ret = ft_preprocess_solo(mini);
	else if (mini->cmd_n > 1)
		ret = ft_preprocess_pipe(mini);
	return (ret);
}

// return 2 si no ha hecho nada, return 0 sin problema, 
// 1 es exit, -1 error

int	ft_builtin_check(t_exec *exec, t_mini *mini)
{
	int	i;

	i = 2;
	if (exec->fd_in == -1 || exec->fd_out == -1)
		return (-1);
	if (ft_strncmp(exec->cmd_mtx[0], "echo", 4) == 0)
		i = ft_echo(exec, ft_get_env_var(mini->env, "HOME") + 1);
	else if (ft_strncmp(exec->cmd_mtx[0], "env", 3) == 0)
		i = ft_env(mini->env, exec->cmd_mtx);
	else if (ft_strncmp(exec->cmd_mtx[0], "export", 6) == 0)
		i = ft_export(mini, exec->cmd_mtx);
	else if (ft_strncmp(exec->cmd_mtx[0], "pwd", 3) == 0)
		i = ft_pwd(exec->cmd_mtx);
	else if (ft_strncmp(exec->cmd_mtx[0], "unset", 5) == 0)
		i = ft_unset(mini, exec->cmd_mtx);
	if (i != 2)
		mini->status = i;
	if (ft_strncmp(exec->cmd_mtx[0], "cd", 2) == 0)
		i = ft_cd(exec->cmd_mtx, mini);
	else if (ft_strncmp(exec->cmd_mtx[0], "exit", 4) == 0)
		i = ft_exit(mini, exec->cmd_mtx);
	return (i);
}

int	ft_no_cmd(t_mini *mini)
{
	t_tokens	*atkn;
	int			i;

	i = 0;
	atkn = mini->tk_lst;
	while (atkn->next)
	{
		if (atkn->type == HEREDOC)
			close(here_doc(atkn->next->value));
		if (atkn->type == REDIRECT_OUTPUT)
			open(atkn->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (i > 1)
			close (i);
		atkn = atkn->next;
	}
	return (0);
}

int	here_doc(char *limiter)
{
	char	*line;
	int		fd[2];
	int		len;

	if (pipe(fd) == -1)
		return (-1);
	signal_handler(HERE_DOC);
	len = ft_strlen(limiter);
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(0);
		if (line == NULL || (ft_strncmp(line, limiter, len) == 0 \
		&& (size_t)(len + 1) == ft_strlen(line)))
			break ;
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	signal_handler(ITERATIVE);
	free(line);
	close(fd[1]);
	return (fd[0]);
}
