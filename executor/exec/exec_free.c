/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:17:24 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/19 12:46:52 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/eminishell.h"

void	ft_free_exec(t_exec *exec)
{
	if (exec->fd_in > 1)
		close (exec->fd_in);
	if (exec->fd_out > 1)
		close (exec->fd_out);
	if (exec->path)
		free(exec->path);
	ft_mtx_free(exec->cmd_mtx);
	free(exec);
}
