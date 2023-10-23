/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:39:12 by erick             #+#    #+#             */
/*   Updated: 2023/10/23 13:16:11 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../executor/header/eminishell.h"

void	ft_cmd_nmb(t_mini	*mini)
{
	t_tokens	*current;

	mini->cmd_n = 0;
	current = mini->tk_lst;
	while (current)
	{
		if (current->type == COMMAND)
			mini->cmd_n++;
		current = current->next;
	}
}
