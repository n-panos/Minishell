/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_solo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:56:23 by nacho             #+#    #+#             */
/*   Updated: 2023/10/19 11:58:32 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eminishell.h"

int	ft_preprocess_solo(t_mini *mini)
{
	t_tokens	*aux_tkn;
	t_exec		*exec;
	int			ret;

	exec = malloc(sizeof(t_exec *));
	if (!exec)
		return (NULL);
	aux_tkn = mini->tk_lst;
	exec->fd_in = 0;
	exec->fd_out = 1;
	while (aux_tkn)
	{
		ft_in_out_type(aux_tkn, exec);
		aux_tkn = aux_tkn->next;
	}
	aux_tkn = mini->tk_lst;
	while (aux_tkn)
	{
		if (aux_tkn->type == COMMAND)
			exec = ft_init_exec(aux_tkn, mini->env);
		aux_tkn = aux_tkn->next;
	}
	ret = ft_builtin_check(exec, mini->env);
	if (ret == 2)
	{
		if (exec->path == NULL)
			ft_error_cmd(exec->cmd_mtx[0]);
		else 
			ft_exec_solo(mini->env, exec);
	}
	ft_free_exec(exec);
	return (ret);
}

pid_t	*ft_exec_solo(char **env, t_exec *exec)
{
	pid_t	*pidc;

	pidc = fork();
	if (pidc == -1)
			exit(EXIT_FAILURE);
	if (pidc == 0)
	{
		if (exec->fd_in > -1)
			dup2(exec->fd_in, 0);
		if (exec->fd_out > -1)
			dup2(exec->fd_out, 1);
		if (execve(exec->path, exec->cmd_mtx, env) == -1)
			exit(EXIT_FAILURE);
	}
	return (pidc);
}

t_exec	*ft_init_exec(t_tokens *token, char **env)
{
	t_tokens	*aux;
	char		*aux_cmd;
	t_exec		*exec;

	exec->path = ft_find_path(env, token->value);
	aux = token;
	aux_cmd = ft_strdup("");
	while (aux && (aux->type == COMMAND || aux->type == ARGUMENT))
	{
		aux_cmd = ft_strfjoin(aux_cmd, aux->type);
		aux_cmd = ft_strfjoin(aux_cmd, " ");
		aux = aux->next;
	}
	exec->cmd_mtx = ft_split(aux_cmd, " ");
	free(aux_cmd);
	return (exec);
}

void	ft_in_out_type(t_tokens *token, t_exec *exec)
{
	if (token->type == HEREDOC)
	{
		close(exec->fd_in);
		exec->fd_in = here_doc(token->value);
	}
	if (token->type == REDIRECT_INPUT)
	{
		close(exec->fd_in);
		exec->fd_in = open(token->value, O_RDONLY);
	}
	if (token->type == REDIRECT_OUTPUT)
	{
		close (exec->fd_out);
		exec->fd_out = open(token->value, \
		O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
}
