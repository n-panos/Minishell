/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erick <erick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 13:37:36 by erick             #+#    #+#             */
/*   Updated: 2023/10/12 21:29:06 by erick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_all_tokens(t_tokens **lst, void (*del)(void *))
{
	t_tokens	*node;
	t_tokens	*tmp;

	if (!lst || !del)
		return ;
	tmp = *lst;
	while (tmp)
	{
		node = tmp->next;
		del(tmp->value);
		if (tmp->tool)
			free(tmp->tool);
		del(tmp);
		tmp = node;
	}
	*lst = NULL;
}
