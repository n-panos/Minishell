/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:20:40 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/10/06 00:05:36 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*create_token(t_parser *tools, int index)
{
	char	*substr;
	t_list	*node;

	substr = ft_substr(tools->input, tools->index, index - tools->index);
	if (substr == NULL)
		return (NULL);
	node = ft_lstnew(substr);
	if (node == NULL)
		return (free(substr), NULL);
	return (node);
}

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
	if (i == tools->index || tools->input == NULL)
		return (NULL);
	node = create_token(tools, i);
	tools->index = i;
	return (node);
}

void	tokenizer(t_parser *tools)
{
	t_list	*node;

	while (1)
	{
		node = get_token(tools);
		if (node == NULL)
			break ;
		ft_lstadd_back(&tools->tokenlst, node);
	}
	free(tools->input);
}

void	parser(t_parser *tools)
{
	t_tokens	*tokens;

	tools->index = 0;
	tools->tokenlst = NULL;
	tokenizer(tools);
	tokens = create_list(tools);
	(void)tokens;
}

void	minishell_loop(t_parser *tools)
{
	char	*input_tmp;

	tools->status = 0;
	while (1)
	{
		tools->input = readline(PROMPT);
		input_tmp = ft_strtrim(tools->input, " \t");
		free(tools->input);
		tools->input = input_tmp;
		if (tools->input == NULL)
		{
			ft_putendl_fd("Error", STDERR_FILENO);
			exit(1);
		}
		add_history(tools->input);
		if (tools->input[0] != '\0')
		{
			if (ft_check_input(tools->input) == 0)
				parser(tools);
			else
				tools->status = 2;
		}
		else
			free(tools->input);
	}
}
