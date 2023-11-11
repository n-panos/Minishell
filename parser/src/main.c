/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:14:02 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/11/11 18:26:42 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../executor/header/eminishell.h"

void	leaks(void)
{
	system("leaks -q minishell");
}

static void	check_argv(int argc, char **argv, char **envp, char ***env)
{
	if (argc != 1 || argv[1] != NULL)
	{
		ft_parser_error("No arguments allowed", '0');
		exit(EXIT_FAILURE);
	}
	if (envp[0] == NULL)
		*env = ft_create_env();
	else
		*env = ft_mtx_cpy(envp);
	if (*env == NULL)
		exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini		mini;
	int			exit_status;

	atexit(leaks);
	mini.tools = malloc(sizeof(t_parser));
	if (mini.tools == NULL)
		return (EXIT_FAILURE);
	check_argv(argc, argv, envp, &mini.env);
	ft_env_rm(&mini, "OLDPWD");
	exit_status = minishell_loop(&mini);
	free_all(&mini);
	return (exit_status);
}
