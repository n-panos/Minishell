/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:17:46 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/10/22 11:59:33 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/eminishell.h"

int	here_doc(char *limiter)
{
	char	*line;
	int		fd[2];

	if (pipe(fd) == -1)
		return (-1);
	line = get_next_line(0);
	while (line)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			break ;
		write(fd[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	close(fd[1]);
	return (fd[0]);
}

void	ft_error_cmd(char *str)
{
	ft_putstr_fd("zsh: command not found: ", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("\n", 1);
}

char	*ft_find_path(char **envp, char *cmd)
{
	char	**pos_paths;
	char	*path;
	int		i;

	i = 0;
	if (envp == NULL)
		return (NULL);
	path = cmd;
	if (ft_strrchr(cmd, '/') == NULL)
	{
		while (envp[i])
		{
			if (ft_strnstr(envp[i], "PATH", 5) && ft_strlen(envp[i]) > 7)
			{
				pos_paths = ft_split(envp[i] + 6, ':');
				path = ft_no_path(cmd, pos_paths);
				ft_mtx_free(pos_paths);
				break ;
			}
			i++;
		}
	}
	else if (access(path, F_OK) != 0)
		return (NULL);
	return (path);
}

char	*ft_no_path(char *cmd, char **pos_paths)
{
	int		i;
	char	*path;

	i = 0;
	while (pos_paths[i])
	{
		path = ft_strjoin(pos_paths[i], "/");
		path = ft_strfjoin(path, cmd);
		if (access(path, F_OK) == 0)
		{
			i = -1;
			break ;
		}
		free (path);
		i++;
	}
	if (i != -1)
		path = NULL;
	return (path);
}
