/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 13:27:26 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/10/06 00:05:36 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_del_quote(char *str, int index)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = malloc(sizeof(char) * ft_strlen(str));
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

int	ft_in_quote(t_parser *tools, int index)
{
	char	*str;
	char	quote_char;

	quote_char = tools->input[index];
	tools->input = ft_del_quote(tools->input, index);
	str = tools->input;
	while (str[index] && str[index] != quote_char)
	{
		if (quote_char == '"' && str[index] == '$')
		{
			index = ft_expander(tools, index);
			str = tools->input;
		}
		else
			index++;
	}
	if (str[index] == quote_char)
		tools->input = ft_del_quote(str, index);
	return (index);
}
