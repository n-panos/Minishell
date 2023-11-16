/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:19:43 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/16 09:34:24 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/eminishell.h"

int	ft_pwd(char **cmd_mtx)
{
	char	str[FILENAME_MAX];

	if (ft_strlen(cmd_mtx[0]) != 3)
		return (2);
	if (cmd_mtx[1] && cmd_mtx[1][0] == '-' && cmd_mtx[1][1] != '\0' && \
	cmd_mtx[1][1] != '-')
	{
		printf("minishell: pwd: -%c", cmd_mtx[1][1]);
		printf(": invalid option\npwd: usage: pwd [-LP]\n");
	}
	if (getcwd(str, sizeof(str)) != NULL)
		printf("%s\n", str);
	return (0);
}
