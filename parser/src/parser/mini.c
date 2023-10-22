/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:39:12 by erick             #+#    #+#             */
/*   Updated: 2023/10/12 18:51:57 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_mini_vars(t_mini	*mini)
{
	t_tokens	*current;

	mini->nb_forks = 1;
	mini->nb_here = 0;
	current = mini->tk_lst;
	while (current)
	{
		if (current->type == NODE_PIPE)
			mini->nb_forks++;
		if (current->type == NODE_HEREDOC)
			mini->nb_here++;
		current = current->next;
	}
}
