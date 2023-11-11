/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erick <erick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:05:52 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/11/11 15:31:43 by erick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../executor/header/eminishell.h"

int	ft_extra_chars(char *input, int index, char specialChar)
{
	int	i;

	i = 1;
	if (specialChar == '|' && input[index + 1] == '|')
		return (0);
	if (specialChar == '>' || specialChar == '<')
	{
		while (input[index + i] && (input[index + i] == '>'
				|| input[index + i] == '<'))
		{
			i++;
			while (input[index + i] && (input[index + i] == ' '
					|| input[index + i] == '\t'))
				index++;
		}
		if (i > 2)
			return (0);
		if (input[index] == '>' && input[index + 1] == '<')
			return (0);
	}
	return (1);
}

int	ft_check_op(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '>' && input[i + 1] == '<')
			return (ft_parser_error("parse error near ", input[i]));
		if (input[i] == '>' && input[i + 1] == '|')
			return (ft_parser_error("parse error near ", input[i]));
		if (input[i] == '|' && input[i + 1] == '<')
			return (ft_parser_error("parse error near ", input[i]));
		if (input[i] == '<' && input[i + 1] == '|')
			return (ft_parser_error("parse error near ", input[i]));
		if (input[i] == '|' && input[i + 1] == '>')
			return (ft_parser_error("parse error near ", input[i]));
	}
	i--;
	if (ft_strchr(DELIMITERS, input[i]))
		return (ft_parser_error("parse error near ", input[i]));
	return (0);
}

/*TODO << >>*/
int	ft_check_input(char *input)
{
	int		i;
	char	quote_char;

	i = -1;
	while (input[++i])
	{
		if (i == 0 && input[i] == '|')
			return (free(input),
				ft_parser_error("parse error near ", input[i]));
		if (input[i] == '"' || input[i] == '\'')
		{
			quote_char = input[i++];
			if (find_quote_close(input, i, quote_char) == 0)
				return (free(input), ft_parser_error("Unclosed quotes", 0));
			while (input[i] != quote_char)
				i++;
		}
		if (ft_extra_chars(input, i, input[i]) == 0)
			return (ft_parser_error("parse error near ", input[i + 1]),
				free(input), 1);
	}
	if (ft_check_op(input))
		return (free(input), 1);
	return (0);
}

int	find_quote_close(char *input, int index, char quote_char)
{
	while (input[index])
	{
		if (input[index] == quote_char)
			return (1);
		index++;
	}
	return (0);
}
