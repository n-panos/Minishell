/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_more.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:09:25 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/19 12:42:38 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/eminishell.h"


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
	return (i);
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
