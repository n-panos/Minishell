/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:11:50 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/10/17 13:16:42 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eminishell.h"

int	ft_execute(t_mini *mini)
{
	int	ret;

	ret = 0;
	if (mini->pipe_n == 0)
		ret = ft_preprocess_solo(mini);
	else if (mini->pipe_n > 0)
		ret = ft_preprocess_pipe(mini);
	return (ret);
}
