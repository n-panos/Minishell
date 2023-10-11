/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erick <erick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:39:12 by erick             #+#    #+#             */
/*   Updated: 2023/10/11 11:37:32 by erick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_mini_vars(t_mini	*mini)
{
	t_tokens	*current;

	mini->nb_forks = 1;
	current = mini->tk_lst;
	while (current)
	{
		if (current->type == NODE_PIPE)
			mini->nb_forks++;
		current = current->next;
	}
}
