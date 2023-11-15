/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_solo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:56:23 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/15 16:17:33 by ediaz--c         ###   ########.fr       */
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
