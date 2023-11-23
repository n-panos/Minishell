/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:18:48 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/23 09:37:32 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/eminishell.h"

int	ft_cd(t_exec *exc, t_mini *mini)
{
	char	str[FILENAME_MAX];

	if (ft_strlen(exc->cmd_mtx[0]) != 2)
		return (2);
	getcwd(str, sizeof(str));
	ft_cd_select(mini, exc);
	if (mini->status == -1)
		mini->status = 1;
	else
		ft_change_old_pwd(mini, str);
	return (0);
}

int	ft_cd_select(t_mini *mini, t_exec *exc)
{
	if (!exc->cmd_mtx[1])
		mini->status = ft_cd_env_var(mini->env, "HOME", exc->fd_out);
	else if (ft_strncmp(exc->cmd_mtx[1], "-", ft_strlen(exc->cmd_mtx[1])) == 0)
		mini->status = ft_cd_env_var(mini->env, "OLDPWD", exc->fd_out);
	else 
	{
		mini->status = ft_cd_standard_dir(exc->cmd_mtx[1]);
		if (mini->status == -1)
			printf("minishell: cd: %s: No such file or directory\n", exc->cmd_mtx[1]);
	}
	return (0);
}

int	ft_cd_standard_dir(char *dir)
{
	char	str[FILENAME_MAX];
	char	*ret;
	int		i;

	if (ft_strncmp(dir, "/", ft_strlen("/")) == 0)
		ret = ft_strdup(dir);
	else
	{
		getcwd(str, sizeof(str));
		ret = ft_strjoin(str, "/");
		ret = ft_strfjoin(ret, dir);
	}
	i = chdir(ret);
	free(ret);
	return (i);
}

int	ft_cd_env_var(char **env, char *str, int out_fd)
{
	char	*dir;
	int		i;

	dir = ft_get_env_var(env, str);
	if (dir == NULL)
	{
		if (ft_strlen(str) == 6)
			printf("minishell: cd: OLDPWD not set\n");
		if (ft_strlen(str) == 4)
			printf("minishell: cd: HOME not set\n");
		return (1);
	}
	if (ft_strlen(dir) == 1)
		return (0);
	dir++;
	i = chdir(dir);
	if (i == -1)
		printf("minishell: cd: %s: No such file or directory\n", dir);
	else if (ft_strlen(str) == 6)
		ft_env_print(dir, out_fd);
	return (i);
}

char	*ft_get_env_var(char **env, char *str)
{
	char	*dir;
	int		i;
	int		len;

	i = 0;
	dir = NULL;
	len = ft_strlen(str);
	while (env[i])
	{
		if (ft_strncmp(env[i], str, len) == 0)
		{
			dir = ft_strchr(env[i], '=');
			if (ft_strlen(env[i]) <= (size_t)len + 1)
				return (dir);
			break ;
		}
		i++;
	}
	return (dir);
}

void	ft_change_old_pwd(t_mini *mini, char *prev_dir)
{
	char	*aux;
	char	str[FILENAME_MAX];

	aux = ft_strjoin("OLDPWD=", prev_dir);
	ft_change_env_var(mini, aux);
	free(aux);
	getcwd(str, sizeof(str));
	aux = ft_strjoin("PWD=", str);
	ft_change_env_var(mini, aux);
	free(aux);
}
