/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erick <erick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:06:12 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/10/12 21:15:13 by erick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

int	ft_found_new_line(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	*ft_memmove_gnl(void *str1, const void *str2, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;
	size_t			i;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	i = 0;
	if (str1 == str2 || n == 0)
		return (str1);
	if (str1 > str2)
	{
		while (n-- > 0)
		{
			s1[n] = s2[n];
		}
	}
	else
	{
		while (i < n)
		{
			s1[i] = s2[i];
			i++;
		}
	}
	return (str1);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*join;

	if (!s1 && !s2)
		return (NULL);
	len1 = ft_strlen_gnl((char *)s1);
	len2 = ft_strlen_gnl((char *)s2);
	join = malloc(sizeof(char) * len1 + len2 + 1);
	if (!join)
		return (NULL);
	ft_memmove_gnl(join, s1, len1);
	ft_memmove_gnl(join + len1, s2, len2);
	join[len1 + len2] = '\0';
	free((char *)s1);
	return (join);
}

size_t	ft_strlen_gnl(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}
