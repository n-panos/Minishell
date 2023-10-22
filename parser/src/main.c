/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:14:02 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/10/22 12:19:02 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../executor/header/eminishell.h"

// void	leaks(void)
// {
// 	system("leaks -q minishell");
// }
int	main(int argc, char **argv, char **envp)
{
	t_mini		mini;

	mini.tools = malloc(sizeof(t_parser));
	if (mini.tools == NULL)
		return (1);
	if (argc != 1 || argv[1] != NULL)
	{
		printf("No se admiten argumentos\n");
		exit(EXIT_FAILURE);
	}
	mini.env = ft_mtx_cpy(envp);
	minishell_loop(&mini);
	free_all(&mini);
	return (0);
}
