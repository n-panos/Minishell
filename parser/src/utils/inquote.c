/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 13:27:26 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/11/29 13:20:00 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../executor/header/eminishell.h"

char	*ft_del_quote(char *str, int index)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = malloc(sizeof(char) * ft_strlen(str));
	if (result == NULL)
		return (NULL);
	while (str[i])
	{
		if (i != index)
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	free(str);
	return (result);
}

/*
*	return -1 en caso de error
*/
int	ft_in_quote(t_parser *tools, int index)
{
	char	*str;
	char	quote_char;

	quote_char = tools->input[index];
	tools->input = ft_del_quote(tools->input, index);
	str = tools->input;
	if (str == NULL)
		return (-1);
	while (str[index] && str[index] != quote_char)
	{
		if (quote_char == '"' && str[index] == '$' && \
		(str[index + 1] != '"' && str[index + 1] != '\''))
		{
			index = ft_expander(tools, index, &str);
			if (index == -1)
				return (-1);
		}
		else
			index++;
	}
	tools->input = ft_del_quote(str, index);
	if (tools->input == NULL)
		return (-1);
	return (index);
}
