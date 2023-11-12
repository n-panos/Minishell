/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:20:40 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/11/12 15:36:30 by ediaz--c         ###   ########.fr       */
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

	in_action = 0;
	while (1)
	{
		input = readline(PROMPT);
		input_tmp = ft_strtrim(input, " \t");
		free(input);
		if (input_tmp[0] != '\0')
			break ;
		free(input_tmp);
	}
	in_action = 1;
	*input_ptr = input_tmp;
	add_history(*input_ptr);
	return (input);
}

int	minishell_loop(t_mini *mini)
{
	t_parser	*tools;
	int			exit_status;

	tools = mini->tools;
	mini->status = 0;
	mini->real_shlvl = 1;
	exit_status = 0;
	while (1)
	{
		if (get_input(&tools->input) == NULL)
			exit(ft_parser_error("Error", STDERR_FILENO));
		if (ft_check_input(tools->input) != 0)
			continue ;
		parser(mini);
		if (tools->error)
			break ;
		if (tools->tokenlst == NULL)
			continue ;
		exit_status = ft_execute(mini);
		if (exit_status > 0)
			break ;
		ft_free_loop(tools, mini);
	}
	return (mini->status);
}
