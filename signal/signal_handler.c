/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 14:19:15 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/11/12 15:37:32 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/includes/minishell.h"

void	sigint_handler(int sign)
{
	printf ("%d\n", sign);
	if (in_action == 0)
	{
		// printf("hola\n");
		write(STDOUT_FILENO, PROMPT, ft_strlen(PROMPT));
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sigterm_handler(int sign)
{
	if (sign)
		return ;
}

void	sigquit_handler(int sign)
{
	if (sign)
		return ;
}

void	create_signal(struct sigaction *signal, void (*funct)(int))
{
	signal->sa_handler = funct;
	sigemptyset(&(*signal).sa_mask);
	signal->sa_flags = 0;
}

void	signal_handler(void)
{
	struct	sigaction	sa_int;
	struct	sigaction	sa_term;
	struct	sigaction	sa_quit;

	create_signal(&sa_int, sigint_handler);
	create_signal(&sa_term, sigterm_handler);
	create_signal(&sa_quit, sigquit_handler);
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
	{
		perror("Error handing signal");
		exit(EXIT_FAILURE);
	}
}
