/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:41:57 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/12/15 16:46:03 by ediaz--c         ###   ########.fr       */
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

void	ft_token_tokenizer(t_tokens **current)
{
	t_tokens	*current_ptr;
	t_tokens	*next;
	t_tokens	*prev;
	char		**split;
	int			i;

	i = -1;
	current_ptr = *current;
	next = current_ptr->next;
	split = ft_split(current_ptr->value, ' ');
	if (split[1] == NULL)
	{
		while (split[++i])
			free(split[i]);
		free(split);
		return ;
	}
	free(current_ptr->value);
	current_ptr->value = ft_strdup(split[++i]);
	if (current_ptr->prev == NULL || current_ptr->prev->type == PIPE)
		current_ptr->type = COMMAND;
	prev = current_ptr;
	current_ptr = current_ptr->next;
	while (split[++i])
	{
		current_ptr = ft_new_token(ft_strdup(split[i]));
		current_ptr->prev = prev;
		prev->next = current_ptr;
		current_ptr->type = ARGUMENT;
		prev = current_ptr;
		current_ptr = current_ptr->next;
	}
	current_ptr = next;
	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

void	check_quotes(t_tokens **lst)
{
	t_tokens	*current;

	current = *lst;
	while (current)
	{
		if (current->quote == OUT_QUOTE)
			ft_token_tokenizer(&current);
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
