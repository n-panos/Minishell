/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erick <erick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:20:40 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/11/09 12:01:58 by erick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../executor/header/eminishell.h"

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

void	parser(t_mini *mini)
{
	t_parser	*tools;
	t_tokens	*tokens;

	tools = mini->tools;
	tools->index = 0;
	tools->error = 0;
	tools->env = mini->env;
	tools->status = mini->status;
	tools->tokenlst = NULL;
	tokenizer(tools);
	if (tools->tokenlst == NULL || tools->error)
		return ;
	tokens = create_list(tools);
	if (tokens == NULL || tools->error)
		return ;
	mini->tk_lst = tokens;
	ft_cmd_nmb(mini);
}

char	*get_input(char	**input_ptr)
{
	char	*input;
	char	*input_tmp;

	while (1)
	{
		input = readline(PROMPT);
		input_tmp = ft_strtrim(input, " \t");
		free(input);
		if (input_tmp[0] != '\0')
			break ;
		free(input_tmp);
	}
	*input_ptr = input_tmp;
	return (input);
}

void	minishell_loop(t_mini *mini)
{
	t_parser	*tools;

	tools = mini->tools;
	mini->status = 0;
	while (1)
	{
		if (get_input(&tools->input) == NULL)
			exit(ft_parser_error("Error", STDERR_FILENO));
		add_history(tools->input);
		if (ft_check_input(tools->input) == 0)
		{
			parser(mini);
			if (tools->error)
				break ;
			if (tools->tokenlst == NULL)
				continue ;
			if (ft_execute(mini) != 0)
				break ;
			ft_free_loop(tools, mini);
		}
		else
			free(tools->input);
	}
}
