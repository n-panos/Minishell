/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 13:37:36 by erick             #+#    #+#             */
/*   Updated: 2023/12/15 15:35:21 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../executor/header/eminishell.h"

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
		del(tmp);
		tmp = node;
	}
	*lst = NULL;
}
