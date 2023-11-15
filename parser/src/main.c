/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:14:02 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/11/15 17:20:33 by nacho            ###   ########.fr       */
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
		ft_putendl_fd("Not arguments allowed", 2);
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
	t_mini			mini;
	int				exit_status;

	//atexit(leaks);
	g_signal = 0;
	mini.tools = malloc(sizeof(t_parser));
	if (mini.tools == NULL)
		return (EXIT_FAILURE);
	signal_handler(ITERATIVE);
	check_argv(argc, argv, envp, &mini.env);
	ft_env_rm(&mini, "OLDPWD");
	ft_change_env_var(&mini, PATH_VAR);
	exit_status = minishell_loop(&mini);
	free_all(&mini);
	return (exit_status);
}
