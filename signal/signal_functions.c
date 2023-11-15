/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:28:40 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/11/15 14:05:04 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/includes/minishell.h"

void	show_ctl(int sig)
{
	struct termios	new;

	tcgetattr(STDIN_FILENO, &new);
	if (sig)
		new.c_lflag |= ECHOCTL;
	else
		new.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &new);
}

void	create_signal(struct sigaction *signal, void (*funct)(int))
{
	signal->sa_handler = funct;
	sigemptyset(&(*signal).sa_mask);
	signal->sa_flags = 0;
}

void	ctrl(int sa)
{
	if (sa == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	else if (sa == SIGQUIT)
		ft_putendl_fd("Quit: 3", STDOUT_FILENO);
}