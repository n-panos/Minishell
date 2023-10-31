/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erick <erick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:33:29 by erick             #+#    #+#             */
/*   Updated: 2023/10/31 10:08:36 by erick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../executor/header/eminishell.h"

void	ft_free_loop(t_parser *tools, t_mini *mini)
{
	ft_free_all_tokens(&mini->tk_lst, free);
	ft_lstclear(&tools->tokenlst, free);
}

void	free_all(t_mini *mini)
{
	int	i;

	if (mini->tk_lst)
		ft_free_all_tokens(&mini->tk_lst, free);
	if (mini->tools->tokenlst)
		ft_lstclear(&mini->tools->tokenlst, free);
	i = -1;
	while (mini->env[++i])
		free(mini->env[i]);
	free(mini->env);
	free(mini->tools);
}
