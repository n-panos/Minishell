/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_more.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:09:25 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/09 14:02:29 by ipanos-o         ###   ########.fr       */
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
			ret = open(atkn->next->value, O_WRONLY | O_APPEND, 0644);
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
		if (atkn->type == REDIRECT_INPUT)
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
	char	*aux;
	char	*shlvl;

	if (ft_strncmp(exec->cmd_mtx[0], "./minishell", 11) != 0  \
	|| ft_strlen(exec->cmd_mtx[0]) != 11)
		return (1);
	if (exec->cmd_mtx[1])
		return (ft_error_cmd(mini, exec->cmd_mtx[1], 0, 0));
	shlvl = ft_get_shlvl(mini->env);
	if (shlvl == NULL)
	{
		ft_error_cmd(mini, exec->cmd_mtx[1], 3, 0);
		shlvl = ft_strdup("SHLVL=1");
	}
	aux = ft_add_to_env(mini->env, shlvl);
	ft_mtx_free(mini->env);
	mini->env = ft_split(aux, '\n');
	free(aux);
	return (0);
}

char	*ft_get_shlvl(char **env)
{
	char	**aux;
	char	*shlvl;
	int		i;
	int		lvl;

	shlvl = NULL;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "SHLVL", 5) == 0)
		{
			aux = ft_split(env[i], '=');
			if (ft_all_isdigit(aux[1]) == 0)
			{
				ft_mtx_free(aux);
				break ;
			}
			lvl = ft_atoi(aux[1]) + 1;
			shlvl = aux[0];
			free(aux[1]);
			free(aux);
			shlvl = ft_strfjoin(shlvl, "=");
			shlvl = ft_strfjoin(shlvl, ft_itoa(lvl));
			break ;
		}
		i++;
	}
	return (shlvl);
}
