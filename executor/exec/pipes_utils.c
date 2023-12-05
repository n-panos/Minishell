/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 12:48:55 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/24 12:48:55 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/eminishell.h"

static int	ft_ret_exit(t_mini *mini, t_tokens *tkn);

t_tokens	*ft_return_pipe(t_tokens *tkn)
{
	while (tkn)
	{
		if (tkn->type == PIPE)
		{
			if (tkn->next)
				tkn = tkn->next;
			break ;
		}
		tkn = tkn->next;
	}
	return (tkn);
}

int	ft_is_exit(t_mini *mini, t_tokens *lst)
{
	t_tokens	*tkn;

	tkn = lst;
	while (tkn)
	{
		if (tkn->type == PIPE)
			break ;
		if (tkn->type == COMMAND && ft_strncmp(tkn->value, "exit", 4) == 0 && \
		ft_strlen(tkn->value) == 4)
			return (ft_ret_exit(mini, tkn));
		if (tkn->type == COMMAND && ft_strncmp(tkn->value, "bash", 4) == 0 && \
		ft_strlen(tkn->value) == 4)
			return (mini->status = 1, 1);
		if (tkn->type == COMMAND && ft_strncmp(tkn->value, "./minishell", 11) \
		== 0 && ft_strlen(tkn->value) == 11)
			return (mini->status = 1, 1);
		if (tkn->type == COMMAND && ft_strncmp(tkn->value, "export", 6) \
		== 0 && ft_strlen(tkn->value) == 6)
			return (mini->status = 1, 1);
		tkn = tkn->next;
	}
	return (0);
}

static int	ft_ret_exit(t_mini *mini, t_tokens *tkn)
{
	if (tkn->next && tkn->next->type == ARGUMENT)
		mini->status = ft_exit_more_args(tkn->next->value);
	else
		mini->status = 1;
	return (1);
}
