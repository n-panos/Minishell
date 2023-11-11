/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_more.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:09:25 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/11 13:24:16 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/eminishell.h"

void	ft_waiting(int n, int *fd)
{
	int	status;

	if (fd[0] > 1)
		close(fd[0]);
	free(fd);
	while (n > 0)
	{
		wait(&status);
		n--;
	}
}

int	check_out(t_mini *mini, t_tokens *tkn)
{
	t_tokens	*atkn;
	int			ret;

	atkn = tkn;
	ret = 1;
	while (atkn)
	{
		if (atkn->type == PIPE)
		{
			if (ret == 1)
				return (-2);
			break ;
		}
		if (ret > 1 && (atkn->type == REDIRECT_OUTPUT \
		|| atkn->type == REDIRECT_APPEND))
			close(ret);
		if (atkn->type == REDIRECT_OUTPUT)
			ret = open(atkn->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (atkn->type == REDIRECT_APPEND)
			ret = open(atkn->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (ret == -1)
			return (ft_error_cmd(mini, atkn->next->value, 0, -1));
		atkn = atkn->next;
	}
	return (ret);
}

int	check_in(t_mini *mini, t_tokens *tkn, int in)
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
		if (atkn->type == REDIRECT_INPUT && atkn->next->type != ARGUMENT)
			ret = in;
		else if (atkn->type == REDIRECT_INPUT)
			ret = open(atkn->next->value, O_RDONLY);
		else if (atkn->type == HEREDOC)
			ret = here_doc(atkn->next->value);
		if (ret == -1)
			return (ft_error_cmd(mini, atkn->next->value, -1, 0));
		atkn = atkn->next;
	}
	return (ret);
}

int	ft_is_minishell(t_mini *mini, t_exec *exec)
{
	if (ft_strncmp(exec->cmd_mtx[0], "./minishell", 11) != 0  \
	|| ft_strlen(exec->cmd_mtx[0]) != 11)
		return (1);
	if (exec->cmd_mtx[1])
		return (ft_error_cmd(mini, exec->cmd_mtx[1], 0, 0));
	ft_change_shlvl(mini, 1);
	ft_mtx_free(exec->cmd_mtx);
	free(exec);
	mini->real_shlvl++;
	return (0);
}

char	*ft_get_shlvl(char **env, int flag)
{
	char	**aux;
	char	*lvl;
	int		i;

	i = 0;
	lvl = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "SHLVL", 5) == 0)
		{
			aux = ft_split(env[i], '=');
			if (ft_all_isdigit(aux[1]) == 1)
			{
				i = ft_atoi(aux[1]) + flag;
				lvl = ft_itoa(i);
			}
			ft_mtx_free(aux);
			break ;
		}
		i++;
	}
	return (lvl);
}
