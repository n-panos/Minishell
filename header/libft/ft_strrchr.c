/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 13:05:56 by ipanos-o          #+#    #+#             */
/*   Updated: 2022/10/19 10:10:46 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	int		i;

	i = 0;
	if (c == '\0')
		return (ft_strchr(s, '\0'));
	if (s == NULL)
		return (NULL);
	str = NULL;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			str = (char *)&s[i];
		i++;
	}
	return (str);
}
