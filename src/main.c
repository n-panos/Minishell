/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:17:09 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/09/21 10:41:26 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eminishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	**env;
	char	*cmd;
	char	*prompt;
	int		i;

	if (argc != 1)
		return (1);
	env = envp;
	while (1)
	{
		prompt = readline("\033[0;32mminishell % \033[0;0m");
		if (prompt[0] != '\0')
			add_history(prompt);
		if (ft_strncmp(prompt, "pwd", ft_strlen(prompt)) == 0)
			ft_exec_pwd();
		if (ft_strncmp(prompt, "env", ft_strlen(prompt)) == 0)
			ft_exec_env(envp);
		i = ft_strncmp(prompt, "dddd", ft_strlen(prompt));
		printf("salida strncmp con dddd = %d\n", i);
	}
	cmd = argv[1];
	return (0);
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