/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puterror.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erick <erick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:12:54 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/10/08 18:07:47 by erick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_parser_error(char *err, char c)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (c != 0)
	{
		ft_putstr_fd(err, STDERR_FILENO);
		write(2, "'", 1);
		write(2, &c, 1);
		write(2, "'\n", 2);
	}
	else
		ft_putendl_fd(err, STDERR_FILENO);
	return (1);
}
