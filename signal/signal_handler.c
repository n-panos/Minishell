/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 14:19:15 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/11/17 17:23:25 by ediaz--c         ###   ########.fr       */
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
		write(STDOUT_FILENO, "\n", 1);
		g_signal = 1;
	}
}

void	handler_process(int sa)
{
	if (sa == SIGINT)
	{
		// write(STDOUT_FILENO, "\n", 1);
		// rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sa == SIGQUIT)
	{
		rl_replace_line("", 0);
		ft_putendl_fd("Quit: 3", STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	child_signal(void)
{
	show_ctl(1);
	signal(SIGINT, ctrl);
	signal(SIGQUIT, ctrl);
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
