/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:45:35 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/10/22 12:19:43 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../executor/header/eminishell.h"

t_tokens	*ft_new_token(char	*value)
{
	t_tokens	*node;

	node = malloc(sizeof(t_tokens));
	if (node == NULL)
		return (NULL);
	node->value = value;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
