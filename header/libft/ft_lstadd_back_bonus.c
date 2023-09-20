/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 18:05:26 by ipanos-o          #+#    #+#             */
/*   Updated: 2022/09/19 11:01:45 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//funcion de revision de listas, añade un elemento mas al final de la lista

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*end;

	end = *lst;
	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			end = ft_lstlast(*lst);
			end->next = new;
		}
	}
}
