/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:18:48 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/12/16 10:33:51 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/eminishell.h"

int	ft_cd(t_exec *exc, t_mini *mini)
{
	char	str[FILENAME_MAX];

	if (ft_strlen(exc->cmd_mtx[0]) != 2)
		return (2);
	if (getcwd(str, sizeof(str)) == NULL)
	{
		ft_null_getcwd(mini);
		return (0);
	}
	else
		ft_cd_select(mini, exc);
	if (mini->status == -1)
		return (mini->status = 1, 5);
	else
		ft_change_old_pwd(mini, str);
	return (0);
}

int	ft_cd_select(t_mini *mini, t_exec *exc)
{
	if (!exc->cmd_mtx[1])
		mini->status = ft_cd_env_var(mini->env, "HOME", exc->fd_out);
	else if (exc->cmd_mtx[1][0] == '\0')
		mini->status = 0;
	else if (ft_strncmp(exc->cmd_mtx[1], "-", ft_strlen(exc->cmd_mtx[1])) == 0)
		mini->status = ft_cd_env_var(mini->env, "OLDPWD", exc->fd_out);
	else
	{
		mini->status = ft_cd_standard_dir(exc->cmd_mtx[1]);
		if (mini->status == -1)
			ft_print_err("minishell: cd: ", exc->cmd_mtx[1], \
			": No such file or directory");
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
			ft_print_err("minishell: cd: OLDPWD not set", NULL, NULL);
		if (ft_strlen(str) == 4)
			ft_print_err("minishell: cd: HOME not set", NULL, NULL);
		return (-1);
	}
	if (ft_strlen(dir) == 1)
		return (0);
	dir++;
	i = chdir(dir);
	if (i == -1)
		ft_print_err("minishell: cd: ", dir, ": No such file or directory");
	else if (ft_strlen(str) == 6)
		ft_env_print(dir, out_fd);
	return (i);
}

void	ft_change_old_pwd(t_mini *mini, char *prev_dir)
{
	char	*aux;
	char	str[FILENAME_MAX];

	aux = ft_strjoin("OLDPWD=", prev_dir);
	ft_change_env_var(mini, aux, 0);
	free(aux);
	getcwd(str, sizeof(str));
	aux = ft_strjoin("PWD=", str);
	ft_change_env_var(mini, aux, 0);
	free(aux);
}
