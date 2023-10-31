/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:18:48 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/10/31 09:18:51 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/eminishell.h"

char	*ft_get_dir(char *dir);

int	ft_cd(char **cmd_mtx)
{
	char	*dir;
	int		i;

	if (ft_strlen(cmd_mtx[0]) != 2)
		return (2);
	i = 0;
	while (cmd_mtx[i])
		i++;
	if (i >= 1)
		return (0);
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
