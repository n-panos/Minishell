/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:14:02 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/12/14 00:55:19 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../executor/header/eminishell.h"

void	leaks(void)
{
	system("leaks -q minishell");
}

/*
╔════════════════════════════════════════════════════════════════════════╗
║                                                                        ║
║   ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗       ║
║   ████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║       ║
║   ██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║       ║
║   ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║       ║
║   ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗  ║
║   ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝  ║
║    by: ipanos-o                                                        ║
║        ediaz--c                                                        ║
╚════════════════════════════════════════════════════════════════════════╝
*/
/******************************************************************************/
void	print_banner(void)
{
	ft_putstr_fd(P"╔═══════════════════════════════════", 2);
	ft_putstr_fd("═════════════════════════════════════╗\n", 2);
	ft_putstr_fd(P"║                                   ", 2);
	ft_putstr_fd("                                     ║\n", 2);
	ft_putstr_fd(P"║"Y"   ███╗   ███╗██╗███╗   ██╗██╗██", 2);
	ft_putstr_fd("█████╗██╗  ██╗███████╗██╗     ██╗       "OFF P"║\n", 2);
	ft_putstr_fd(P"║"Y"   ████╗ ████║██║████╗  ██║██║██", 2);
	ft_putstr_fd("╔════╝██║  ██║██╔════╝██║     ██║       "OFF P"║\n", 2);
	ft_putstr_fd(P"║"Y"   ██╔████╔██║██║██╔██╗ ██║██║██", 2);
	ft_putstr_fd("█████╗███████║█████╗  ██║     ██║       "OFF P"║\n", 2);
	ft_putstr_fd(P"║"Y"   ██║╚██╔╝██║██║██║╚██╗██║██║╚═", 2);
	ft_putstr_fd("═══██║██╔══██║██╔══╝  ██║     ██║       "OFF P"║\n", 2);
	ft_putstr_fd(P"║"Y"   ██║ ╚═╝ ██║██║██║ ╚████║██║██", 2);
	ft_putstr_fd("█████║██║  ██║███████╗███████╗███████╗  "OFF P"║\n", 2);
	ft_putstr_fd(P"║"Y"   ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚═", 2);
	ft_putstr_fd("═════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝  "OFF P"║\n", 2);
	ft_putstr_fd(P"║"R"    by: ipanos-o                ", 2);
	ft_putstr_fd("                                        "P"║\n", 2);
	ft_putstr_fd(P"║"R"        ediaz--c                ", 2);
	ft_putstr_fd("                                        "P"║\n", 2);
	ft_putstr_fd(P"╚═══════════════════════════════════", 2);
	ft_putstr_fd("═════════════════════════════════════╝\n"OFF, 2);
}

static void	check_argv(int argc, char **argv, char **envp, t_mini *mini)
{
	mini->flag_path = 1;
	if (argc != 1 || argv[1] != NULL)
	{
		ft_putendl_fd("Not arguments allowed", 2);
		exit(EXIT_FAILURE);
	}
	if (envp[0] == NULL)
	{
		mini->flag_path = 0;
		mini->env = ft_create_env();
	}
	else
	{
		if (getenv("PATH") == NULL)
			mini->flag_path = 0;
		mini->env = ft_mtx_cpy(envp);
	}
	if (mini->env == NULL)
		exit(EXIT_FAILURE);
	if (envp[0] && ft_increment_shlvl(mini->env) == NULL)
		exit(EXIT_FAILURE);
	ft_env_rm(mini, "OLDPWD");
}

int	main(int argc, char **argv, char **envp)
{
	t_mini			mini;
	int				exit_status;

	g_signal = 0;
	mini.tools = malloc(sizeof(t_parser));
	if (mini.tools == NULL)
		return (EXIT_FAILURE);
	print_banner();
	signal_handler(ITERATIVE);
	check_argv(argc, argv, envp, &mini);
	exit_status = minishell_loop(&mini, mini.tools);
	free_all(&mini);
	return (exit_status);
}
