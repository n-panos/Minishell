/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 14:19:15 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/11/13 14:34:22 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/includes/minishell.h"

void	handler_iterative(int sa)
{
	if (sa == SIGINT)
	{
		/*TODO eliminar ^C*/
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handler_heredoc(int sa)
{
	char	eof;

	eof = EOF;
	if (sa == SIGINT)
	{
		/*TODO eliminar ^C*/
		ft_putendl_fd(&eof, 1);
	}
}

void	create_signal(struct sigaction *signal, void (*funct)(int))
{
	signal->sa_handler = funct;
	sigemptyset(&(*signal).sa_mask);
	signal->sa_flags = 0;
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
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("Error handing signal");
		exit(EXIT_FAILURE);
	}
}
