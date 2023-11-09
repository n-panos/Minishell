/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:39:12 by erick             #+#    #+#             */
/*   Updated: 2023/11/09 17:01:10 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../executor/header/eminishell.h"

void	ft_cmd_nmb(t_mini *mini)
{
	t_tokens	*current;

	mini->cmd_n = 0;
	if (mini->tk_lst == NULL)
		return ;
	current = mini->tk_lst;
	while (current)
	{
		if (current->type == COMMAND)
			mini->cmd_n++;
		current = current->next;
	}
}
