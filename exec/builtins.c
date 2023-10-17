/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:40:09 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/10/17 11:59:03 by ipanos-o         ###   ########.fr       */
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

// return 2 no ha hecho nada, return 0 sin problema, 1 es exit, -1 error

int	ft_builtin_check(t_exec *exec, char **env)
{
	int	i;

	i = 2;
	if (ft_strncmp(exec->cmd_mtx[0], "cd", 2));
		i = ft_exec_cd(exec->cmd_mtx);
	if (ft_strncmp(exec->cmd_mtx[0], "echo", 4));
		i = ft_exec_echo(exec->cmd_mtx);
	if (ft_strncmp(exec->cmd_mtx[0], "env", 3));
		i = ft_exec_env(env, cmd_mtx);
	return (i);
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