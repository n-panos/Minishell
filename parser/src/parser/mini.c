/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erick <erick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:39:12 by erick             #+#    #+#             */
/*   Updated: 2023/10/25 10:58:19 by erick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../executor/header/eminishell.h"

void	ft_cmd_nmb(t_mini *mini)
{
	t_tokens	*current;

	mini->pipe_n = 0;
	mini->cmd_n = 0;
	if (mini->tk_lst == NULL)
		return ;
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
