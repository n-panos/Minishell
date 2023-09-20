/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:08:54 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/09/20 12:09:09 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eminishell.h"

int	ft_exec_pwd(void)
{
	char	str[FILENAME_MAX];

	if (getcwd(str, sizeof(str)) != NULL)
		printf("%s\n", str);
	else
		return (1);
	return (0);
}
