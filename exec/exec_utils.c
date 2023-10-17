/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:17:46 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/10/17 13:18:12 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eminishell.h"

int	here_doc(char *limiter)
{
	char	*line;
	int		fd[2];

	if (pipe(fd) == -1)
		error();
	line = get_next_line(0);
	while (line)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			break ;
		write(fd[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	close(fd[1]);
	return (fd[0]);
}
