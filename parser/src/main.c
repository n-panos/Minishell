/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erick <erick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:14:02 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/11/11 13:27:41 by erick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../executor/header/eminishell.h"

void	leaks(void)
{
	system("leaks -q minishell");
}

int	main(int argc, char **argv, char **envp)
{
	t_mini		mini;
	int			exit_status;

	atexit(leaks);
	mini.tools = malloc(sizeof(t_parser));
	if (mini.tools == NULL)
		return (EXIT_FAILURE);
	if (argc != 1 || argv[1] != NULL)
	{
		printf("No se admiten argumentos\n");
		exit(EXIT_FAILURE);
	}
	mini.env = ft_mtx_cpy(envp);
	exit_status = minishell_loop(&mini);
	free_all(&mini);
	return (exit_status);
}
