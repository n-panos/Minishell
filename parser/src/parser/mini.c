/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:39:12 by erick             #+#    #+#             */
/*   Updated: 2023/10/22 12:19:43 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../executor/header/eminishell.h"

void	ft_mini_vars(t_mini	*mini)
{
	t_tokens	*current;

	mini->pipe_n = 0;
	current = mini->tk_lst;
	while (current)
	{
		if (current->type == PIPE)
			mini->pipe_n++;
		current = current->next;
	}
}
