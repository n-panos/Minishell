/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:18:48 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/07 17:58:50 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/eminishell.h"

char	*ft_get_dir(char *dir);
char	*ft_get_zdotdir(char **env);

int	ft_cd(char **cmd_mtx, char **env)
{
	char	*dir;
	int		i;

	if (ft_strlen(cmd_mtx[0]) != 2)
		return (2);
	if (!cmd_mtx[1])
		dir = ft_get_zdotdir(env);
	else
		dir = ft_get_dir(cmd_mtx[1]);
	i = chdir(dir);
	if (i == -1)
		printf("minishell: cd: %s: No such file or directory\n", dir);
	free(dir);
	return (0);
}

char	*ft_get_dir(char *dir)
{
	char	str[FILENAME_MAX];
	char	*ret;

	if (ft_strncmp(dir, "/", ft_strlen("/")) == 0)
		ret = ft_strdup(dir);
	else
	{
		getcwd(str, sizeof(str));
		ret = ft_strjoin(str, "/");
		ret = ft_strfjoin(ret, dir);
	}
	return (ret);
}

char	*ft_get_zdotdir(char **env)
{
	char	*dir;
	int		i;
	char	**aux;

	i = 0;
	dir = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "USER_ZDOTDIR", 12) == 0)
		{
			aux = ft_split(env[i], '=');
			dir = aux[1];
			free(aux[0]);
			free(aux);
			break ;
		}
		i++;
	}
	return (dir);
}
