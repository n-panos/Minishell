/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erick <erick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:20:40 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/10/11 11:37:11 by erick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	tokenizer(t_parser *tools)
{
	t_list	*node;

	while (1)
	{
		node = get_token(tools);
		if (node == NULL)
			break ;
		if (ft_is_empty((char *)node->content))
			ft_lstdelone(node, free);
		else
			ft_lstadd_back(&tools->tokenlst, node);
	}
	free(tools->input);
}

t_tokens	*parser(t_parser *tools)
{
	t_tokens	*tokens;

	tools->index = 0;
	tools->error = 0;
	tools->tokenlst = NULL;
	tokenizer(tools);
	if (tools->tokenlst == NULL || tools->error)
		return (NULL);
	if (ft_check_nodes(tools) == 0)
		return (NULL);
	tokens = create_list(tools);
	if (tokens == NULL || tools->error)
		return (NULL);
	return (tokens);
}

char	*get_input(void)
{
	char	*input;
	char	*input_tmp;

	input = readline(PROMPT);
	input_tmp = ft_strtrim(input, " \t");
	free(input);
	input = input_tmp;
	if (input == NULL)
		return (NULL);
	return (input);
}

void	minishell_loop(t_mini *mini)
{
	t_parser	*tools;

	tools = mini->tools;
	tools->status = 0;
	while (1)
	{
		tools->input = get_input();
		if (tools->input == NULL)
			exit(ft_parser_error("Error", STDERR_FILENO));
		add_history(tools->input);
		if (tools->input[0] != '\0' && ft_check_input(tools->input) == 0)
		{
			mini->tk_lst = parser(tools);
			if (tools->error)
				break ;
			ft_mini_vars(mini);
			/*EXECUTOR*/
			ft_free_loop(tools, mini);
		}
		else
			free(tools->input);
	}
}
