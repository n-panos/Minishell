/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:56:35 by erick             #+#    #+#             */
/*   Updated: 2023/11/11 18:29:05 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static char	*get_pwd(void)
{
	char	*pwd_big;
	char	*pwd_path;

	pwd_big = ft_calloc(PATH_MAX, sizeof(char));
	if (pwd_big == NULL || getcwd(pwd_big, PATH_MAX) == NULL)
		return (NULL);
	pwd_path = ft_substr(pwd_big, 0, ft_strlen(pwd_big));
	free(pwd_big);
	return (pwd_path);
}

static char	*get_env_pwd(void)
{
	char	*pwd_path;
	char	*pwd;

	pwd_path = get_pwd();
	if (pwd_path == NULL)
		return (NULL);
	pwd = ft_strjoin("PWD=", pwd_path);
	free(pwd_path);
	return (pwd);
}

static char	*get_env_last_cmd(void)
{
	char	*env_path;
	char	*env_tmp;
	char	*env;

	env_path = get_pwd();
	if (env_path == NULL)
		return (NULL);
	env_tmp = ft_strjoin(env_path, "/minishell");
	free(env_path);
	if (env_tmp == NULL)
		return (NULL);
	env = ft_strjoin("_=", env_tmp);
	free(env_tmp);
	return (env);
}

static char	**free_create_env(char *pwd, char *shlvl,
	char *last_cmd, char **env)
{
	if (pwd)
		free(pwd);
	if (shlvl)
		free(shlvl);
	if (last_cmd)
		free(last_cmd);
	if (env)
		free(env);
	return (NULL);
}

char	**ft_create_env(void)
{
	char	*pwd;
	char	*shlvl;
	char	*last_cmd;
	char	**env;

	pwd = get_env_pwd();
	shlvl = ft_strdup("SHLVL=1");
	last_cmd = get_env_last_cmd();
	env = malloc(sizeof(char *) * 4);
	if (!pwd ||!shlvl ||!last_cmd || !env)
		return (free_create_env(pwd, shlvl, last_cmd, env));
	env[0] = pwd;
	env[1] = shlvl;
	env[2] = last_cmd;
	env[3] = NULL;
	return (env);
}
