/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_more.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:42:26 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/10/31 13:00:16 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eminishell.h"

typedef struct s_pope
{
	int		out;
	t_exec	*cmd1;
	t_exec	*cmd2;
	int		*fd;
}	t_pope;

void	ft_preprocess_pipe(t_mini *mini)
{
	int			i;
	int			in_out;
	t_exec		*odd_one;
	t_tokens	*atkn;

	i = 1;
	atkn = mini->tk_lst;
	in_out = 0;
	while (atkn && i < mini->cmd_n)
	{
		in_out = ft_exec_two();
		i += 2;
		atkn = ft_check_pipe_type(atkn);
	}
	if (i == mini->cmd_n)
	{
		odd_one = ft_init_exec(atkn, mini->env, in_out, );
	}
}

int	ft_exec_two(t_mini *mini, t_tokens *tkn, int in)
{
	t_pope		*pope;
	int			*fd;
	t_tokens	*atkn;

	atkn = tkn;
	pope = ft_config_pipe(atkn, mini->env, in);
	atkn = ft_return_pipe(tkn);
	atkn = ft_return_pipe(atkn);
	if (pope->cmd2->fd_out == 1 && atkn)
	{
		fd = ft_calloc(2, sizeof(int *));
		if (pipe(fd) == -1)
			exit(EXIT_FAILURE);
		pope->cmd2->fd_out = fd[0];
		pope->out = fd[1];
	}
	ft_exec_solo(mini->env, pope->cmd1);
	ft_exec_solo(mini->env, pope->cmd2);
	ft_free_pipes(pope);
	return (pope->out);
}

t_pope	*ft_config_pipe(t_tokens *tkn, char **env, int in)
{
	t_pope		*pope;

	pope = ft_calloc(1, sizeof(t_pope));
	if (!pope)
		return (-1);
	pope->out = 1;
	pope->cmd1 = ft_add_cmd(tkn, env, in);
	tkn = ft_return_pipe(tkn);
	pope->cmd2 = ft_add_cmd(tkn, env, 0);
	if (pope->cmd1->fd_out == 1 && pope->cmd2->fd_in == 0)
	{
		pope->fd = ft_calloc(2, sizeof(int *));
		if (pipe(pope->fd) == -1)
			exit(EXIT_FAILURE);
		pope->cmd1->fd_out = pope->fd[0];
		pope->cmd2->fd_in = pope->fd[1];
	}
	return (pope);
}

t_exec	*ft_add_cmd(t_tokens *tkn, char **env, int in)
{
	t_exec	*ret;
	int		out;

	in = ft_check_in(tkn, in);
	out = ft_check_out(tkn);
	while (tkn)
	{
		if (tkn->type == COMMAND)
		{
			ret = ft_init_exec(tkn, env, in, out);
			break ;
		}
		tkn = tkn->next;
	}
	return (ret);
}

int	ft_check_out(t_tokens *tkn)
{
	t_tokens	*atkn;
	int			ret;

	atkn = tkn;
	ret = 1;
	while (atkn)
	{
		if (atkn->type == PIPE)
			return (-1);
		if (ret > 1 && (atkn->type == REDIRECT_OUTPUT \
		|| atkn->type == REDIRECT_APPEND))
			close(ret);
		if (atkn->type == REDIRECT_OUTPUT)
			ret = open(atkn->next->value, \
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (atkn->type == REDIRECT_APPEND)
			ret = open(atkn->next->value, \
			O_WRONLY | O_APPEND, 0644);
		atkn = atkn->next;
	}
	return (ret);
}

int	ft_check_in(t_tokens *tkn, int in)
{
	t_tokens	*atkn;
	int			ret;

	atkn = tkn;
	ret = in;
	while (atkn)
	{
		if (atkn->type == PIPE)
			break ;
		if (ret > 0 && (atkn->type == HEREDOC \
		|| atkn->type == REDIRECT_INPUT))
			close(ret);
		if (atkn->type == REDIRECT_INPUT)
			ret = open(atkn->next->value, O_RDONLY);
		else if (atkn->type == HEREDOC)
			ret = here_doc(atkn->next->value);
		atkn = atkn->next;
	}
	return (ret);
}

t_tokens	*ft_return_pipe(t_tokens *tkn)
{
	while (tkn)
	{
		if (tkn->type == PIPE)
		{
			if (tkn->next)
				tkn = tkn->next;
			break ;
		}
		tkn = tkn->next;
	}
	return (tkn);
}
