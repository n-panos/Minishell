/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erick <erick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 18:09:23 by erick             #+#    #+#             */
/*   Updated: 2023/10/11 11:42:23 by erick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*get_token(t_parser *tools)
{
	int		i;
	t_list	*node;

	if (tools->index > (int)ft_strlen(tools->input))
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
	if ((int)ft_strlen(tools->input) == tools->index || tools->input == NULL)
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
	if (node == NULL)
	{
		tools->error = 1;
		return (free(substr), NULL);
	}
	return (node);
}

t_list	*ft_rotate(t_list *current, t_list **lst)
{
	t_list	*cmd;
	t_list	*end_cmd;
	t_list	*tmp;
	char	*nx_content;

	cmd = current->next->next;
	if (cmd == NULL)
		return (NULL);
	*lst = cmd;
	end_cmd = cmd;
	while (end_cmd->next)
	{
		nx_content = end_cmd->next->content;
		if (ft_strchr(DELIMITERS, nx_content[0]))
			break ;
		end_cmd = end_cmd->next;
	}
	tmp = current;
	current = current->next;
	ft_lstdelone(tmp, free);
	tmp = end_cmd->next;
	end_cmd->next = current;
	current->next = tmp;
	return (cmd);
}

int	ft_check_nodes(t_parser *tools)
{
	t_list	*current;
	t_list	*prev;
	char	*content;
	char	*prev_content;

	current = tools->tokenlst;
	prev = NULL;
	prev_content = NULL;
	while (current)
	{
		content = current->content;
		if (prev == NULL && content[0] == '<')
			current = ft_rotate(current, &tools->tokenlst);
		else if (prev && prev_content[0] == '|'
			&& content[0] == '<' && content[1] == '\0')
			current = ft_rotate(current, &prev->next);
		if (current == NULL)
			return (0);
		prev = current;
		prev_content = prev->content;
		current = current->next;
	}
	return (1);
}
