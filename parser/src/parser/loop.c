/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:20:40 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/11/29 13:25:04 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../executor/header/eminishell.h"

void	tokenizer(t_parser *tools)
{
	t_list	*node;

	while (1)
	{
		(*tools).expander = 0;
		(*tools).quote = 0;
		node = get_token(tools);
		if (node == NULL)
			break ;
		if (ft_is_empty((char *)node->content) && tools->expander == 1)
			ft_lstdelone(node, free);
		else
		{
			if (ft_is_empty((char *)node->content))
			{
				free(node->content);
				node->content = ft_strdup("");
			}
			ft_lstadd_back(&tools->tokenlst, node);
		}
		if ((*tools).quote)
			(*node).quote = 1;
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

char	*get_input(char	**input_ptr, struct termios *original)
{
	char	*input;
	char	*input_tmp;

	tcsetattr(STDIN_FILENO, TCSANOW, original);
	while (1)
	{
		if (isatty(STDIN_FILENO))
			input = readline(PROMPT);
		if (input == NULL)
		{
			ft_putendl_fd("exit", 1);
			exit(0);
		}
		input_tmp = ft_strtrim(input, " \t");
		free(input);
		if (input_tmp[0] != '\0')
			break ;
		free(input_tmp);
	}
	*input_ptr = input_tmp;
	add_history(*input_ptr);
	return (input);
}

void	check_status(t_mini *mini)
{
	if (g_signal != 0)
	{
		mini->status = g_signal;
		g_signal = 0;
	}
}

int	minishell_loop(t_mini *mini, t_parser *tools)
{
	int				exit_status;
	struct termios	original;

	mini->status = 0;
	exit_status = 0;
	tcgetattr(STDIN_FILENO, &original);
	while (1)
	{
		check_status(mini);
		if (get_input(&tools->input, &original) == NULL)
			exit(ft_parser_error("Error", STDERR_FILENO));
		if (ft_check_input(tools->input, &mini->status) != 0)
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
