/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 14:19:15 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/11/19 18:18:57 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/includes/minishell.h"

void	handler_iterative(int sa)
{
	if (sa == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handler_heredoc(int sa)
{
	if (sa == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		g_signal = 1;
	}
}

void	child_signal(void)
{
	struct sigaction	sa;

	create_signal(&sa, ctrl);
	show_ctl(1);
	if (sigaction(SIGINT, &sa, NULL) == -1
		|| sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("Error handing signal");
		exit(EXIT_FAILURE);
	}
}

/*
*	@param state	- ITERATIVE
*					- HEREDOC
*					- PROCESS
*/
void	signal_handler(int state)
{
	struct sigaction	sa;

	signal(SIGQUIT, SIG_IGN);
	if (state == ITERATIVE)
		create_signal(&sa, handler_iterative);
	else if (state == HERE_DOC)
		create_signal(&sa, handler_heredoc);
	show_ctl(0);
	if (state != PROCESS && sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("Error handing signal");
		exit(EXIT_FAILURE);
	}
}
