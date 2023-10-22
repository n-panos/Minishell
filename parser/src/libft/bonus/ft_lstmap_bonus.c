/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 20:55:18 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/07/11 14:10:49 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map;
	t_list	*node;
	void	*ptr;

	if (!lst || !del || !f)
		return (0);
	map = NULL;
	while (lst)
	{
		ptr = f(lst->content);
		node = ft_lstnew(ptr);
		if (!node)
		{
			del (ptr);
			ft_lstclear(&map, (*del));
			return (0);
		}
		ft_lstadd_back(&map, node);
		lst = lst->next;
	}
	return (map);
}
