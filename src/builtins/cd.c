/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:09:06 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/09/27 12:33:56 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eminishell.h"

char	*ft_get_dir(char *dir);

int	ft_exec_cd(char **cmd_mtx)
{
	char	*dir;

	if (ft_strlen(cmd_mtx[0]) != 2)
		return (2);
	dir = ft_get_dir(cmd_mtx[1]);
	return (chdir(dir));
}

char	*ft_get_dir(char *dir)
{
	char	str[FILENAME_MAX];
	char	*ret;

	if (ft_strncmp(dir, "/", ft_strlen("/")) == 0)
		ret = dir;
	else
	{
		getcwd(str, sizeof(str));
		ret = ft_strjoin(str, "/");
		ret = ft_strfjoin(ret, dir);
	}
	return (ret);
}
