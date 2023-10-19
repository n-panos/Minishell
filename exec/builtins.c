/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:40:09 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/10/18 11:34:45 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eminishell.h"

void	leaks(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **envp)
{
	char	*cmd;
	char	*prompt;
	int		i;
	t_prg	*prg;

	atexit(leaks);
	if (argc != 1)
		return (1);
	prg = malloc(sizeof(prg));
	prg->env = envp;
	while (1)
	{
		prompt = readline("\033[0;32mminishell % \033[0;0m");
		if (prompt[0] != '\0')
			add_history(prompt);
		i = ft_builtins(prg, prompt);
		if (i == 1)
			break ;
	}
	cmd = argv[0];
	return (0);
}

//exit cierra el programa devolviendo un uno, se puede gestionar con un flag en struct

int	ft_builtins(t_prg *prg, char *prompt)
{
	int	i;

	i = 0;
	if (ft_strncmp(prompt, "pwd", ft_strlen("pwd")) == 0)
		i = ft_exec_pwd();
	else if (ft_strncmp(prompt, "env", ft_strlen("env")) == 0)
		i = ft_exec_env(prg->env, 0);
	else if (ft_strncmp(prompt, "export", ft_strlen("export")) == 0)
		i = ft_exec_export(prg->env);
	else if (ft_strncmp(prompt, "exit", ft_strlen("exit")) == 0)
		i = 1;
	else if (ft_strncmp(prompt, "echo", ft_strlen("echo")) == 0)
		i = ft_exec_echo(prompt);
	else if (ft_strncmp(prompt, "cd", ft_strlen("cd")) == 0)
		i = ft_exec_cd(prompt);
	else if (ft_strncmp(prompt, "unset", ft_strlen("unset")) == 0)
		i = ft_exec_unset(prg, prompt);
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