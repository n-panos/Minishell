/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:41:57 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/12/15 12:53:01 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../executor/header/eminishell.h"

static void	ft_add_type(t_tokens *lst)
{
	t_tokens	*current;

	current = lst;
	while (current)
	{
		if (ft_is_command(current))
			current->type = COMMAND;
		else if (ft_is_op(current) == PIPE)
			current->type = PIPE;
		else if (ft_is_op(current) == REDIRECT_INPUT)
			current->type = REDIRECT_INPUT;
		else if (ft_is_op(current) == REDIRECT_OUTPUT)
			current->type = REDIRECT_OUTPUT;
		else if (ft_is_op(current) == REDIRECT_APPEND)
			current->type = REDIRECT_APPEND;
		else if (ft_is_op(current) == HEREDOC)
			current->type = HEREDOC;
		else if (ft_is_delimiter(current))
			current->type = DELIMITER;
		else if (ft_is_argument(current))
			current->type = ARGUMENT;
		current = current->next;
	}
}

static t_tokens	*ft_create(t_parser *tools)
{
	t_list		*current_list;
	t_tokens	*list;
	t_tokens	*node;
	char		*value;

	list = NULL;
	current_list = tools->tokenlst;
	if (current_list == NULL)
		return (NULL);
	while (current_list)
	{
		value = ft_strdup(current_list->content);
		if (value == NULL)
			break ;
		node = ft_new_token(value);
		(*node).quote = (*current_list).quote;
		ft_add_back_token(&list, node);
		current_list = current_list->next;
	}
	if (current_list != NULL)
		ft_free_all_tokens(&list, free);
	return (list);
}

void	check_quotes(t_tokens **lst)
{
	t_tokens	*current;

	current = *lst;
	while (current)
	{
		if (current->quote)
		{
			current->value = ft_del_quote(&current->value, 0);
			current->value = ft_del_quote(&current->value, \
			ft_strlen(current->value) - 1);
		}
		current = current->next;
	}
}

t_tokens	*create_list(t_parser *tools)
{
	t_tokens	*lst;

	lst = ft_create(tools);
	if (lst == NULL)
		return (NULL);
	ft_add_type(lst);
	check_quotes(&lst);
	return (lst);
}
