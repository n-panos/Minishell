/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erick <erick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 19:06:28 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/10/12 21:43:40 by erick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_create_here(char *path, char *del)
{
	int		fd;	
	char	*input;

	fd = open(path, O_CREAT | O_WRONLY, 0777);
	while (1)
	{
		write(0, "heredoc> ", 9);
		input = get_next_line(0);
		if (ft_strncmp(input, del, ft_strlen(del)) == 0
			&& ft_strlen(del) == ft_strlen(input) - 1)
			break ;
		write(fd, input, ft_strlen(input));
		free(input);
	}
	free(input);
	close(fd);
}

char	*ft_get_heredoc(char *del)
{
	char	*file;
	char	*path;
	int		index;
	char	*cindex;

	file = "/tmp/here_doc";
	index = 1;
	while (1)
	{
		cindex = ft_itoa(index);
		path = ft_strjoin(file, cindex);
		free(cindex);
		if (path == NULL)
			continue ;
		if (access(path, F_OK) == -1)
			break ;
		free(path);
		index++;
	}
	ft_create_here(path, del);
	return (path);
}

void	ft_check_heredoc(t_mini *mini)
{
	t_tokens	*current;

	current = mini->tk_lst;
	while (current)
	{
		if (current->type == NODE_HEREDOC)
			current->tool = ft_get_heredoc(current->next->value);
		current = current->next;
	}
}
