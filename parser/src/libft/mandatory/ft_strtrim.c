/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:41:27 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/07/11 14:10:49 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	startchar(char const *str, char const *set)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_strchr(set, str[i]) == 0)
			break ;
		i++;
	}
	return (i);
}

int	endchar(char const *str, char const *set)
{
	int	i;
	int	len;

	i = 1;
	len = ft_strlen(str);
	while (i <= len)
	{
		if (ft_strchr(set, str[len - i]) == 0)
			break ;
		i++;
	}
	return (len - i + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	char	*str;
	int		start;
	int		end;

	if (!s1)
		return (0);
	if (!set)
		return ((char *)s1);
	start = startchar(s1, set);
	end = endchar(s1, set);
	if (set == NULL)
		return (ft_strdup(s1));
	if (end <= start)
		return (ft_strdup(""));
	len = end - start;
	if (len == 0)
		return (0);
	str = ft_substr(s1, start, len);
	return (str);
}
