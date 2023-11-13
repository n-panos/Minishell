/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 14:19:15 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/11/13 16:59:40 by ediaz--c         ###   ########.fr       */
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
		write(STDOUT_FILENO, "\n", 1);
}

void	handler_process(int sa)
{
	int		kill_result;
	pid_t	pid;

	pid = getpid();
	kill_result = kill(pid, sa);
	if (kill_result == EXIT_SUCCESS)
	{
		if (sa == SIGINT)
		{
			g_signal = 130;
			write(STDOUT_FILENO, "\n", 1);
		}
		else if (sa == SIGQUIT)
		{
			g_signal = 131;
			ft_putendl_fd("Quit: 3", STDOUT_FILENO);
		}
		exit(1);
	}
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
	if (state == HERE_DOC)
	{
		signal(SIGQUIT, SIG_IGN);
		create_signal(&sa, handler_heredoc);
	}
	if (state == PROCESS)
	{
		create_signal(&sa, handler_process);
	}
	show_ctl(0);
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("Error handing signal");
		exit(EXIT_FAILURE);
	}
}
