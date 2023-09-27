/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:40:09 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/09/27 13:20:05 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eminishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*cmd;
	char	*prompt;
	int		i;

	if (argc != 1)
		return (1);
	while (1)
	{
		prompt = readline("\033[0;32mminishell % \033[0;0m");
		if (prompt[0] != '\0')
			add_history(prompt);
		i = ft_builtins(envp, prompt);
		if (i == 1)
			break ;
	}
	cmd = argv[0];
	return (0);
}

int	ft_builtins(char **env, char *prompt)
{
	int	i;

	i = 0;
	if (ft_strncmp(prompt, "pwd", ft_strlen(prompt)) == 0)
		i = ft_exec_pwd();
	else if (ft_strncmp(prompt, "env", ft_strlen("env")) == 0)
		i = ft_exec_env(env, 0);
	else if (ft_strncmp(prompt, "export", ft_strlen("export")) == 0)
		i = ft_exec_export(env);
	else if (ft_strncmp(prompt, "exit", ft_strlen("exit")) == 0)
		i = 1;
	else if (ft_strncmp(prompt, "echo", ft_strlen("echo")) == 0)
		i = ft_exec_echo(prompt);
	else if (ft_strncmp(prompt, "cd", ft_strlen("cd")) == 0)
		i = ft_exec_cd(prompt);
	else if (ft_strncmp(prompt, "unset", ft_strlen("unset")) == 0)
		env = ft_exec_unset(env, prompt);
	return (i);
}

/*			si envp existe, env = envp, 
			si envp no existe(env -i ./minishell) , valores minimos son :
				PWD
				SHLVL=1
				PATH=
				_=./minishell
char **ft_env(char **envp)
{
}*/