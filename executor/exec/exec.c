/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:16:49 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/21 19:10:36 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/eminishell.h"

// return es -1 si hubo algun error de ejecucion, 0 si ejecuto bien, 
// 1 si viene del comando exit y hay que cerrar la consola

int	ft_execute(t_mini *mini)
{
	int			ret;

	ret = 0;
	mini->status = 0;
	mini->pipe_status = 0;
	if (mini->cmd_n == 0)
		ret = ft_no_cmd(mini);
	if (mini->cmd_n == 1)
		ret = ft_preprocess_solo(mini);
	else if (mini->cmd_n > 1)
		ret = ft_preprocess_pipe(mini, 0);
	return (ret);
}

// return 2 si no ha hecho nada, return 0 sin problema, 
// 1 es exit, -1 error

int	ft_no_cmd(t_mini *mini)
{
	t_tokens	*atkn;
	int			i;

	i = 0;
	atkn = mini->tk_lst;
	while (atkn->next)
	{
		if (atkn->type == HEREDOC)
			close(here_doc(atkn->next->value));
		if (atkn->type == REDIRECT_OUTPUT)
			open(atkn->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (i > 1)
			close (i);
		atkn = atkn->next;
	}
	return (0);
}
