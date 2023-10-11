/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erick <erick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:33:29 by erick             #+#    #+#             */
/*   Updated: 2023/10/11 11:34:40 by erick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_loop(t_parser *tools, t_mini *mini)
{
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
