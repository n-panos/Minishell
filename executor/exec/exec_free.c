/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:17:24 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/12/16 12:12:39 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/eminishell.h"

void	ft_free_exec(t_mini *mini, t_exec *exec)
{
	char	*aux;
	int		i;

	if (exec->cmd_mtx[0] && ft_strncmp(exec->cmd_mtx[0], "env", 3) != 0)
	{
		i = 0;
		if (ft_strncmp(exec->cmd_mtx[0], "unset", 6) == 0)
		{
			while (exec->cmd_mtx[i] && exec->cmd_mtx[i + 1])
				++i;
		}
		aux = ft_strjoin("_=", exec->cmd_mtx[i]);
		ft_change_env_var(mini, aux, 1);
		free(aux);
	}
	if (exec->fd_in > 1)
		close (exec->fd_in);
	if (exec->fd_out > 1)
		close (exec->fd_out);
	if (exec->path)
		free(exec->path);
	ft_mtx_free(exec->cmd_mtx);
	free(exec);
}
