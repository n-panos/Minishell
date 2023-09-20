/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 17:23:14 by ipanos-o          #+#    #+#             */
/*   Updated: 2022/09/14 12:33:30 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//copia string 

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*copy;
	int		j;

	i = ft_strlen(s1) + 1;
	j = 0;
	copy = malloc(i);
	if (!copy)
		return (NULL);
	while (s1[j] != '\0')
	{
		copy[j] = s1[j];
		j++;
	}
	copy[j] = '\0';
	return (copy);
}
