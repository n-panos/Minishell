/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:39:12 by erick             #+#    #+#             */
/*   Updated: 2023/10/24 11:42:21 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../executor/header/eminishell.h"

void	ft_cmd_nmb(t_mini	*mini)
{
	t_tokens	*current;

	mini->pipe_n = 0;
	mini->cmd_n = 0;
	current = mini->tk_lst;
	while (current)
	{
		if (current->type == COMMAND)
			mini->cmd_n++;
		if (current->type == PIPE)
			mini->pipe_n++;
		current = current->next;
	}
}
