/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:40:09 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/10/20 10:54:38 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eminishell.h"

void	leaks(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **envp)
{
	char	*aux;
	char	*prompt;
	int		i;
	t_mini	*mini;

	atexit(leaks);
	if (argc != 1)
		return (1);
	mini = malloc(sizeof(t_mini));
	mini->env = envp;
	mini->pipe_n = 0;
	aux = argv[0];
	if (aux)
		printf("hola");
	while (1)
	{
		prompt = readline("\033[0;32mminishell % \033[0;0m");
		if (prompt[0] != '\0')
			add_history(prompt);
		i = ft_builtins(mini, prompt);
		if (i == 1)
			break ;
	}
	return (0);
}

//exit cierra el programa devolviendo un uno, se puede gestionar con un flag en struct

int	ft_builtins(t_mini *mini, char *prompt)
{
	int	i;
	char	**aux_mtx;

	i = 0;
	aux_mtx = ft_split(prompt, ' ');
	if (ft_strncmp(prompt, "pwd", ft_strlen("pwd")) == 0)
		i = ft_pwd(aux_mtx);
	else if (ft_strncmp(prompt, "env", ft_strlen("env")) == 0)
		i = ft_env(mini->env, aux_mtx);
	else if (ft_strncmp(prompt, "export", ft_strlen("export")) == 0)
		i = ft_export(mini->env);
	else if (ft_strncmp(prompt, "exit", ft_strlen("exit")) == 0)
		i = 1;
	else if (ft_strncmp(prompt, "echo", ft_strlen("echo")) == 0)
		i = ft_echo(aux_mtx);
	else if (ft_strncmp(prompt, "cd", ft_strlen("cd")) == 0)
		i = ft_cd(aux_mtx);
	else if (ft_strncmp(prompt, "unset", ft_strlen("unset")) == 0)
		i = ft_unset(mini, prompt);
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