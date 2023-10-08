/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erick <erick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:45:59 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/10/08 17:24:20 by erick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
*	Retorna 1 si el argumento es un delimitador del heredoc, y no expande
*/
int	ft_is_operator(t_parser *tools, int index)
{
	int		i;
	char	*str;

	i = index - 1;
	str = tools->input;
	while (i >= 0 && (str[i] == ' ' || str[i] == '\t'))
		i--;
	if (str[i] == '<')
	{
		i--;
		if (i >= 0 && str[i] == '<')
			return (1);
	}
	return (0);
}

/*
*	Retorna el index
*/
int	ft_not_expand(t_parser *tools, int index)
{
	int	i;

	i = index;
	while (tools->input[i])
	{
		if (ft_strchr(DELIMITERS, tools->input[i]))
			break ;
		else if (tools->input[i] == ' ' || tools->input[i] == '\0')
			break ;
		i++;
	}
	return (i);
}
