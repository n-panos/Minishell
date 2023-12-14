/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 13:27:26 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/12/12 18:49:12 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../executor/header/eminishell.h"

char	*ft_del_quote(char **str, int index)
{
	char	*result;
	char	*str_ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str_ptr = *str;
	result = malloc(sizeof(char) * ft_strlen(str_ptr));
	if (result == NULL)
		return (NULL);
	while (str_ptr[i])
	{
		if (i != index)
			result[j++] = str_ptr[i];
		i++;
	}
	result[j] = '\0';
	free(*str);
	*str = result;
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
	if (ft_del_quote(&tools->input, index) == NULL)
		return (-1);
	str = tools->input;
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
	tools->input = str;
	if (ft_del_quote(&tools->input, index) == NULL)
		return (-1);
	if (tools->input[index] == '"' || tools->input[index] == '\'')
		tools->not_increment = 1;
	return (index);
}
