/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erick <erick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:41:57 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/10/12 21:33:10 by erick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*pinta la información de los tokens*/
void	print_lst_doble(t_tokens *lst)
{
	t_tokens	*current;
	int			i;

	current = lst;
	i = 0;
	while (current)
	{
		printf("Token %d\n", ++i);
		printf("NEXT: %p\n", current->next);
		printf("PREV: %p\n", current->prev);
		printf("VALUE: %s LEN: %zu\n", current->value, ft_strlen(current->value));
		printf("TOOLS: %s\n", current->tool);
		if (current->type == NODE_ARGUMENT)
			printf("TYPE: ARGUMENT\n");
		else if (current->type == NODE_COMMAND)
			printf("TYPE: COMMAND\n");
		else if (current->type == NODE_DELIMITER)
			printf("TYPE: DELIMITIER\n");
		else if (current->type == NODE_HEREDOC)
			printf("TYPE: HEREDOC\n");
		else if (current->type == NODE_PIPE)
			printf("TYPE: PIPE\n");
		else if (current->type == NODE_REDIRECT_APPEND)
			printf("TYPE: APPEND\n");
		else if (current->type == NODE_REDIRECT_INPUT)
			printf("TYPE: INPUT\n");
		else if (current->type == NODE_REDIRECT_OUTPUT)
			printf("TYPE: OUTPUT\n");
		printf("\n");
		current = current->next;
	}
}

static void	ft_add_type(t_tokens *lst)
{
	t_tokens	*current;

	current = lst;
	while (current)
	{
		if (ft_is_command(current))
			current->type = NODE_COMMAND;
		else if (ft_is_op(current) == NODE_PIPE)
			current->type = NODE_PIPE;
		else if (ft_is_op(current) == NODE_REDIRECT_INPUT)
			current->type = NODE_REDIRECT_INPUT;
		else if (ft_is_op(current) == NODE_REDIRECT_OUTPUT)
			current->type = NODE_REDIRECT_OUTPUT;
		else if (ft_is_op(current) == NODE_REDIRECT_APPEND)
			current->type = NODE_REDIRECT_APPEND;
		else if (ft_is_op(current) == NODE_HEREDOC)
			current->type = NODE_HEREDOC;
		else if (ft_is_delimiter(current))
			current->type = NODE_DELIMITER;
		else if (ft_is_argument(current))
			current->type = NODE_ARGUMENT;
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
		ft_add_back_token(&list, node);
		current_list = current_list->next;
	}
	if (current_list != NULL)
		ft_free_all_tokens(&list, free);
	return (list);
}

t_tokens	*create_list(t_parser *tools)
{
	t_tokens	*lst;

	lst = ft_create(tools);
	if (lst == NULL)
		return (NULL);
	ft_add_type(lst);
	return (lst);
}
