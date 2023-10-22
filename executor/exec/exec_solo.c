/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_solo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:56:23 by nacho             #+#    #+#             */
/*   Updated: 2023/10/22 11:59:33 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/eminishell.h"

int	ft_preprocess_solo(t_mini *mini)
{
	t_tokens	*aux_tkn;
	t_exec		*exec;
	int			ret;

	aux_tkn = mini->tk_lst;
	while (aux_tkn)
	{
		if (aux_tkn->type == COMMAND)
			break ;
		aux_tkn = aux_tkn->next;
	}
	exec = ft_init_exec(aux_tkn, mini->env);
	ft_in_out_type(mini->tk_lst, exec);
	if (exec == NULL)
		return (-1);
	ret = ft_builtin_check(exec, mini);
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

pid_t	ft_exec_solo(char **env, t_exec *exec)
{
	pid_t	pidc;

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

	exec = malloc(sizeof(t_exec *));
	if (!exec)
		return (NULL);
	exec->fd_in = 0;
	exec->fd_out = 1;
	exec->path = ft_find_path(env, token->value);
	aux = token;
	aux_cmd = ft_strdup("");
	while (aux && (aux->type == COMMAND || aux->type == ARGUMENT))
	{
		aux_cmd = ft_strfjoin(aux_cmd, aux->value);
		aux_cmd = ft_strfjoin(aux_cmd, " ");
		aux = aux->next;
	}
	exec->cmd_mtx = ft_split(aux_cmd, ' ');
	free(aux_cmd);
	return (exec);
}

void	ft_in_out_type(t_tokens *token, t_exec *exec)
{
	t_tokens	*aux_token;

	aux_token = token;
	while (aux_token)
	{
		if (aux_token->type == HEREDOC)
		{
			close(exec->fd_in);
			exec->fd_in = here_doc(aux_token->value);
		}
		if (aux_token->type == REDIRECT_INPUT)
		{
			close(exec->fd_in);
			exec->fd_in = open(aux_token->value, O_RDONLY);
		}
		if (aux_token->type == REDIRECT_OUTPUT)
		{
			close (exec->fd_out);
			exec->fd_out = open(aux_token->value, \
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		aux_token = aux_token->next;
	}
}
