/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_solo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:56:23 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/16 13:32:28 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/eminishell.h"

int	ft_preprocess_solo(t_mini *mini)
{
	t_tokens	*aux_tkn;
	t_exec		*exec;
	int			status;
	int			ret;

	aux_tkn = mini->tk_lst;
	exec = ft_add_cmd(aux_tkn, mini, 0);
	if (exec == NULL)
		return (-1);
	ret = ft_exec_type(mini, exec, 0, 0);
	wait(&status);
	signal_handler(ITERATIVE);
	return (ret);
}
