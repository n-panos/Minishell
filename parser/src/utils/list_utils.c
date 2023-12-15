/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:40:26 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/12/15 18:27:16 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../executor/header/eminishell.h"

static void	ft_remake_token(t_tokens **token, char *new_value, t_tokens **prev)
{
	t_tokens	*current;

	current = *token;
	free(current->value);
	current->value = ft_strdup(new_value);
	if (current->prev == NULL || current->prev->type == PIPE)
		current->type = COMMAND;
	else
		current->type = ARGUMENT;
	*prev = current;
	current = current->next;
	*token = current;
}

static void	ft_free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

static char	**ft_check_node(t_tokens *node)
{
	char	**split;

	split = ft_split(node->value, ' ');
	if (split[1] == NULL)
	{
		ft_free_split(split);
		return (NULL);
	}
	return (split);
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
	split = ft_check_node(current_ptr);
	if (split == NULL)
		return ;
	ft_remake_token(&current_ptr, split[++i], &prev);
	while (split[++i])
	{
		current_ptr = ft_new_token(ft_strdup(split[i]));
		current_ptr->prev = prev;
		prev->next = current_ptr;
		current_ptr->type = ARGUMENT;
		prev = current_ptr;
	}
	prev->next = next;
	if (next)
		next->prev = prev;
	ft_free_split(split);
}
