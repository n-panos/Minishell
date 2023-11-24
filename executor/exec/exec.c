/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:16:49 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/24 12:23:53 by ipanos-o         ###   ########.fr       */
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
	if (ft_is_env_i_mini(mini) == 0)
		return (ret);
	else if (mini->cmd_n == 0)
		ret = ft_no_cmd(mini->tk_lst, STDIN_FILENO);
	else if (mini->pipe_n == 0)
		ret = ft_preprocess_solo(mini);
	else if (mini->pipe_n >= 1)
		ret = ft_preprocess_pipe(mini, 0);
	return (ret);
}

// return 2 si no ha hecho nada, return 0 sin problema, 
// 1 es exit, -1 error

int	ft_no_cmd(t_tokens *tkn, int in)
{
	t_tokens	*atkn;

	atkn = tkn;
	while (atkn->next)
	{
		if (atkn->type == PIPE)
			break ;
		if (atkn->type == HEREDOC)
			close(here_doc(atkn->next->value, in));
		if (atkn->type == REDIRECT_OUTPUT)
			close(open(atkn->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644));
		atkn = atkn->next;
	}
	return (0);
}
