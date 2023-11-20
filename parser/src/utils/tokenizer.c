/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 18:09:23 by erick             #+#    #+#             */
/*   Updated: 2023/11/20 16:38:58 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../executor/header/eminishell.h"

t_list	*get_token(t_parser *tools)
{
	int		i;
	t_list	*node;

	if (tools->index > (int)ft_strlen(tools->input))
		return (NULL);
	if ((int)ft_strlen(tools->input) == tools->index || tools->input == NULL)
		return (NULL);
	i = tools->index;
	if (tools->input[i] == ' ' || tools->input[i] == '\t')
		i = ft_space_char(tools, i);
	if (ft_strchr(DELIMITERS, tools->input[i]))
		i = ft_delimiters(tools, i);
	else if (!ft_strchr(DELIMITERS, tools->input[i]))
		i = ft_arguments(tools, i);
	if (i == -1)
		return (NULL);
	node = create_token(tools, i);
	if (node == NULL)
		return (NULL);
	tools->index = i;
	return (node);
}

t_list	*create_token(t_parser *tools, int index)
{
	char	*substr;
	t_list	*node;

	substr = ft_substr(tools->input, tools->index, index - tools->index);
	if (substr == NULL)
	{
		tools->error = 1;
		return (NULL);
	}
	node = ft_lstnew(substr);
	(*node).quote = 0;
	if (node == NULL)
	{
		tools->error = 1;
		return (free(substr), NULL);
	}
	return (node);
}
