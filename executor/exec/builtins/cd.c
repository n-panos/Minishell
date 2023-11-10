/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:18:48 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/10 12:50:07 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/eminishell.h"

int		ft_get_dir(char *dir);
int		ft_get_home(char **env, char *str);
void	ft_change_oldpwd(t_mini *mini, char *prev_dir);

int	ft_cd(char **cmd_mtx, t_mini *mini)
{
	char	str[FILENAME_MAX];

	if (ft_strlen(cmd_mtx[0]) != 2)
		return (2);
	getcwd(str, sizeof(str));
	if (!cmd_mtx[1])
		mini->status = ft_get_home(mini->env, "HOME");
	else if (ft_strncmp(cmd_mtx[1], "-", ft_strlen(cmd_mtx[1])) == 0)
	{
		mini->status = ft_get_home(mini->env, "OLDPWD");
		if (mini->status == 1)
			printf("minishell: cd: OLDPWD not set\n");
	}
	else
		mini->status = ft_get_dir(cmd_mtx[1]);
	if (mini->status == -1 && cmd_mtx[1])
		printf("minishell: cd: %s: No such file or directory\n", cmd_mtx[1]);
	if (mini->status == -1)
		mini->status = 1;
	else
		ft_change_oldpwd(mini, str);
	return (0);
}

int	ft_get_dir(char *dir)
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

int	ft_get_home(char **env, char *str)
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
			if (ft_strlen(env[i]) <= 5)
				return (0);
			break ;
		}
		i++;
	}
	if (dir == NULL)
		return (1);
	dir++;
	i = chdir(dir);
	if (i == -1)
		printf("minishell: cd: %s: No such file or directory\n", dir);
	return (i);
}

void	ft_change_oldpwd(t_mini *mini, char *prev_dir)
{
	char	*aux;
	char	*add;

	aux = ft_strjoin("OLDPWD=", prev_dir);
	add = ft_add_to_env(mini->env, aux);
	free(aux);
	ft_mtx_free(mini->env);
	mini->env = ft_split(add, '\n');
	free(add);
}
