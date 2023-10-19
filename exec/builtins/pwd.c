/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:08:54 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/10/18 11:36:37 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eminishell.h"

int	ft_pwd(void)
{
	char	str[FILENAME_MAX];

	if (getcwd(str, sizeof(str)) != NULL)
		printf("%s\n", str);
	else
		return (1);
	return (0);
}
