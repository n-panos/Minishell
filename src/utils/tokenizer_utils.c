/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:08:07 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/10/06 00:05:36 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_space_char(t_parser *tools, int index)
{
	char	*str;

	str = tools->input;
	while (str[index] && (str[index] == ' ' || str[index] == '\t'))
	{
		index++;
		tools->index++;
	}
	return (index);
}

int	ft_delimiters(t_parser *tools, int index)
{
	char	*str;
	char	delimiter_char;

	str = tools->input;
	delimiter_char = str[index];
	while (str[index] != '\0' && (str[index] == delimiter_char))
		index++;
	return (index);
}

int	ft_arguments(t_parser *tools, int index)
{
	char	*str;

	str = tools->input;
	while (str[index])
	{
		if (str[index] == '"' || str[index] == '\'')
		{
			index = ft_in_quote(tools, index);
			str = tools->input;
		}
		if (str[index] == '$')
		{
			index = ft_expander(tools, index);
			str = tools->input;
		}
		if (str[index] == ' ' || str[index] == '\t')
			break ;
		if (ft_strchr(DELIMITERS, str[index]))
			break ;
		index++;
	}
	return (index);
}
