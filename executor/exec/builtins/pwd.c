/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:08:54 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/10/23 11:13:05 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/eminishell.h"

int	ft_pwd(char **cmd_mtx)
{
	char	str[FILENAME_MAX];

	if (ft_strlen(cmd_mtx[0]) != 3)
		return (2);
	if (cmd_mtx[1] && cmd_mtx[1][0] == '-' && cmd_mtx[1][1] != '\0' && cmd_mtx[1][1] != '-')
	{
		printf("minishell: pwd: -%c", cmd_mtx[1][1]);
		printf(": invalid option\npwd: usage: pwd [-LP]\n");
	}
	if (getcwd(str, sizeof(str)) != NULL)
		printf("%s\n", str);
	return (0);
}
