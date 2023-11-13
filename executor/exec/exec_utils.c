/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:17:59 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/13 17:04:59 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/eminishell.h"

t_exec	*ft_add_cmd(t_tokens *tkn, t_mini *mini, int in)
{
	t_exec	*ret;
	int		out;

	ret = NULL;
	in = check_in(mini, tkn, in);
	out = check_out(mini, tkn);
	while (tkn)
	{
		if (tkn->type == COMMAND)
		{
			ret = ft_init_exec(tkn, mini->env, in, out);
			if (ret == NULL)
				mini->status = 12;
			break ;
		}
		tkn = tkn->next;
	}
	return (ret);
}

t_exec	*ft_init_exec(t_tokens *token, char **env, int in, int out)
{
	t_tokens	*aux;
	char		*aux_cmd;
	t_exec		*exec;

	exec = ft_calloc(1, sizeof(t_exec));
	if (!exec)
		return (NULL);
	exec->fd_in = in;
	exec->fd_out = out;
	exec->path = ft_find_path(env, token->value);
	aux = token;
	aux_cmd = ft_strdup("");
	while (aux && (aux->type == COMMAND || aux->type == ARGUMENT))
	{
		aux_cmd = ft_join_n(aux_cmd, aux->value, " ");
		aux = aux->next;
	}
	exec->cmd_mtx = ft_split(aux_cmd, ' ');
	free(aux_cmd);
	return (exec);
}

int	ft_exec_type(t_mini *mini, t_exec *exec, int in, int out)
{
	int	i;

	i = ft_builtin_check(exec, mini);
	if (i == 2)
	{
		if (ft_is_minishell(mini, exec) == 0)
			return (0);
		if (exec->path == NULL)
			i = ft_error_cmd(mini, exec->cmd_mtx[0], in, out);
		else if (exec->fd_in != -1 && exec->fd_out != -1)
		{
			ft_exec_solo(mini->env, exec);
			i = 0;
		}
	}
	ft_free_exec(mini, exec);
	return (i);
}

void	ft_exec_solo(char **env, t_exec *exec)
{
	pid_t	pidc;

	pidc = fork();
	if (pidc == -1)
	{
		printf("minishell: error while forking process\n");
		exit(EXIT_FAILURE);
	}
	if (pidc == 0)
	{
		if (exec->fd_in > 0)
		{
			dup2(exec->fd_in, 0);
			close(exec->fd_in);
		}
		if (exec->fd_out > 1)
		{
			dup2(exec->fd_out, 1);
			close(exec->fd_out);
		}
		exec->ret = execve(exec->path, exec->cmd_mtx, env);
		printf("minishell: executing error\n");
		exit(EXIT_FAILURE);
	}
}

int	ft_is_minishell(t_mini *mini, t_exec *exec)
{
	if (ft_strncmp(exec->cmd_mtx[0], "./minishell", 11) != 0  \
	|| ft_strlen(exec->cmd_mtx[0]) != 11)
		return (1);
	if (exec->cmd_mtx[1])
		return (ft_error_cmd(mini, exec->cmd_mtx[1], 0, 0));
	ft_change_shlvl(mini, 1);
	ft_free_exec(mini, exec);
	mini->real_shlvl++;
	return (0);
}
