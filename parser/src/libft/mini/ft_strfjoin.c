/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 12:27:20 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/10/22 12:29:56 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strfjoin(char *s1, char const *s2)
{
	char	*cat;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	cat = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!cat)
		return (NULL);
	while (s1[i] != '\0')
	{
		cat[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		cat[i] = s2[j];
		i++;
		j++;
	}
	cat[i] = '\0';
	free(s1);
	return (cat);
}
