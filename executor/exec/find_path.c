/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:45:22 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/23 09:54:32 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/eminishell.h"

char	*ft_find_path(char **envp, char *cmd, int flag)
{
	char	**pos_paths;
	char	*path;
	char	*aux;

	if (envp == NULL || cmd == NULL)
		return (NULL);
	if (ft_strrchr(cmd, '/') == NULL)
	{
		aux = ft_get_env_var(envp, "PATH");
		if (aux == NULL && flag == 0)
			aux = PATH_VAR;
		if (aux == NULL)
			return (NULL);
		pos_paths = ft_split(aux + 1, ':');
		path = ft_no_path(cmd, pos_paths);
		ft_mtx_free(pos_paths);
	}
	else if (access(cmd, F_OK) != 0)
		return (NULL);
	else
		path = ft_strdup(cmd);
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
