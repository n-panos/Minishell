/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 14:19:15 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/11/14 00:46:48 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/includes/minishell.h"

void	off_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

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
		write(STDOUT_FILENO, "\n", 1);
}

void	handler_process(int sa)
{
	if (sa == SIGINT)
	{
		signal(sa, SIG_DFL);
		write(STDOUT_FILENO, "\n\n", 1);
	}
	g_signal = 130;
}

/*
*	@param state	- ITERATIVE
*					- PROCESS
*					- HEREDOC
*/
void	signal_handler(int state)
{
	struct sigaction	sa;

	if (state == ITERATIVE || state == HERE_DOC)
		signal(SIGQUIT, SIG_IGN);
	if (state == ITERATIVE)
		create_signal(&sa, handler_iterative);
	else if (state == HERE_DOC)
		create_signal(&sa, handler_heredoc);
	else if (state == PROCESS)
	{
		signal(SIGINT, SIG_DFL);
		write(STDOUT_FILENO, "\n\n", 2);
		return ;
	}
		// create_signal(&sa, handler_process);
	show_ctl(0);
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("Error handing signal");
		exit(EXIT_FAILURE);
	}
}
