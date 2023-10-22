/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:33:29 by erick             #+#    #+#             */
/*   Updated: 2023/10/22 12:19:43 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../executor/header/eminishell.h"

void	del_file(t_mini *mini)
{
	t_tokens	*current;

	current = mini->tk_lst;
	while (current)
	{
		if (current->type == HEREDOC)
			unlink(current->tool);
		current = current->next;
	}
}

void	ft_free_loop(t_parser *tools, t_mini *mini)
{
	del_file(mini);
	ft_free_all_tokens(&mini->tk_lst, free);
	ft_lstclear(&tools->tokenlst, free);
}

void	free_all(t_mini *mini)
{
	if (mini->tk_lst)
		ft_free_all_tokens(&mini->tk_lst, free);
	if (mini->tools->tokenlst)
		ft_lstclear(&mini->tools->tokenlst, free);
	free(mini->tools);
}
