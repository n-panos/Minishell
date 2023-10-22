/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typed.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:56:01 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/10/12 18:45:22 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_command(t_tokens *token)
{
	if (token->value[0] == '>' || token->value[0] == '<')
		return (0);
	if (token->prev == NULL)
		return (1);
	if (token->prev->type == NODE_ARGUMENT
		&& token->prev->prev->type == NODE_REDIRECT_INPUT)
		return (1);
	if (token->prev->type == NODE_ARGUMENT
		&& token->prev->prev->type == NODE_REDIRECT_OUTPUT)
		return (1);
	else if (token->prev->type == NODE_PIPE)
		return (1);
	return (0);
}

int	ft_is_op(t_tokens *token)
{
	int	len;

	len = ft_strlen(token->value);
	if (len == 1)
	{
		if (token->value[0] == '|')
			return (NODE_PIPE);
		else if (token->value[0] == '<')
			return (NODE_REDIRECT_INPUT);
		else if (token->value[0] == '>')
			return (NODE_REDIRECT_OUTPUT);
	}
	else
	{
		if (token->value[0] == '<')
			return (NODE_HEREDOC);
		else if (token->value[0] == '>')
			return (NODE_REDIRECT_APPEND);
	}
	return (0);
}

int	ft_is_delimiter(t_tokens *token)
{
	if (token->prev->type == NODE_HEREDOC)
		return (1);
	return (0);
}

int	ft_is_argument(t_tokens *token)
{
	(void)token;
	return (1);
}
