/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:08:07 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/12/15 14:55:13 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../executor/header/eminishell.h"

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

/*
*	Retorna -1 en caso de error
*/
int	ft_arguments(t_parser *tools, int index)
{
	char	*str;

	str = tools->input;
	while (str[index])
	{
		tools->not_increment = 0;
		if (index > -1 && (str[index] == '"' || str[index] == '\''))
		{
			index = ft_in_quote(tools, index);
			str = tools->input;
		}
		if (index > -1 && str[index] == '$')
		{
			index = ft_expander(tools, index, &str, OUT_QUOTE);
		}
		if (index > -1 && (str[index] == ' ' || str[index] == '\t'))
			break ;
		if (index == -1 || (ft_strchr(DELIMITERS, str[index])))
			break ;
		if (tools->not_increment == 0)
			index++;
	}
	if (index == -1)
		tools->error = 1;
	return (index);
}

int	ft_is_empty(char *str)
{
	if (ft_strlen(str) == 2)
	{
		if (str[0] == ' ' && str[1] == '\0')
			return (1);
	}
	else if (str[0] == '\0')
		return (1);
	return (0);
}
