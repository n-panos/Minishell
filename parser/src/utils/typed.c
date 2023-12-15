/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typed.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:56:01 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/12/15 16:47:11 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../executor/header/eminishell.h"

int	ft_is_command(t_tokens *token)
{
	if (token->value[0] == '>'
		|| token->value[0] == '<' || token->value[0] == '|')
		return (0);
	if (token->prev == NULL)
		return (1);
	if (token->prev->type == ARGUMENT
		&& token->prev->prev->type == REDIRECT_INPUT)
		return (1);
	if (token->prev->type == ARGUMENT
		&& token->prev->prev->type == REDIRECT_OUTPUT)
		return (1);
	else if (token->prev->type == PIPE)
		return (1);
	else if (token->prev->type == DELIMITER && (token->prev->prev->prev == NULL
			|| token->prev->prev->prev->type == PIPE))
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
			return (PIPE);
		else if (token->value[0] == '<')
			return (REDIRECT_INPUT);
		else if (token->value[0] == '>')
			return (REDIRECT_OUTPUT);
	}
	else if (len == 2)
	{
		if (token->value[0] == '<' && token->value[1] == '<')
			return (HEREDOC);
		else if (token->value[0] == '>' && token->value[1] == '>')
			return (REDIRECT_APPEND);
	}
	return (0);
}

int	ft_is_delimiter(t_tokens *token)
{
	if (token->prev->type == HEREDOC)
		return (1);
	return (0);
}

int	ft_is_argument(t_tokens *token)
{
	(void)token;
	return (1);
}
