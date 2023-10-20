/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:49:01 by nacho             #+#    #+#             */
/*   Updated: 2023/10/20 12:50:12 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eminishell.h"

int	*ft_add_used(int *prev_used, int new_used)
{
	int	*aux;
	int	i;

	i = 0;
	while (prev_used[i])
		i++;
	i++;
	aux = malloc(sizeof(int) * (i + 1));
	aux[i] = '\0';
	i--;
	if (new_used == 0)
		aux[i] = -1;
	else
		aux[i] = new_used;
	while (i > 0)
	{
		i--;
		aux[i] = prev_used[i];
	}
	free(prev_used);
	return (aux);
}

int	ft_check_list(int *list, int n)
{
	int	i;

	i = 0;
	while (list[i])
	{
		if (list[i] == n)
			return (1);
		i++;
	}
	return (0);
}
