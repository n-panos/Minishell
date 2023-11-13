/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 14:19:15 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/11/13 18:49:59 by ediaz--c         ###   ########.fr       */
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

void	ctr_c_process(int sa)
{
	printf("a%d\n", sa);
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

	if (state == ITERATIVE)
	{
		signal(SIGQUIT, SIG_IGN);
		create_signal(&sa, handler_iterative);
	}
	else if (state == HERE_DOC)
	{
		signal(SIGQUIT, SIG_IGN);
		create_signal(&sa, handler_heredoc);
	}
	else if (state == PROCESS)
	{
		signal(SIGINT, SIG_DFL);
		create_signal(&sa, ctr_c_process);
		signal(SIGQUIT, SIG_DFL);
		// return ;
	}
	show_ctl(0);
	if (sigaction(SIGINT, &sa, NULL) == -1
		|| sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("Error handing signal");
		exit(EXIT_FAILURE);
	}
}
