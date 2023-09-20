/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 11:40:11 by ipanos-o          #+#    #+#             */
/*   Updated: 2022/09/14 12:31:58 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//escribe en el fd el string "s"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s + i != NULL && s[i] != '\0')
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}
