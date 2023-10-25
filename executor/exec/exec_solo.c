/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_solo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: erick <erick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:56:23 by nacho             #+#    #+#             */
/*   Updated: 2023/10/25 11:23:24 by erick            ###   ########.fr       */
=======
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:56:23 by nacho             #+#    #+#             */
/*   Updated: 2023/10/25 12:13:25 by nacho            ###   ########.fr       */
>>>>>>> f5388440bcdacf64d5a74f584801ee52011b568c
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
		if (exec->fd_in > 0)
			dup2(exec->fd_in, 0);
		if (exec->fd_out > 1)
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

	exec = ft_calloc(1, sizeof(t_exec));
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
	t_tokens	*a_tkn;

	a_tkn = token;
	while (a_tkn)
	{
		if (exec->fd_in > 0 && (a_tkn->type == HEREDOC \
		|| a_tkn->type == REDIRECT_INPUT))
			close(exec->fd_in);
		if (a_tkn->type == HEREDOC)
			exec->fd_in = here_doc(a_tkn->next->value);
		else if (a_tkn->type == REDIRECT_INPUT)
			exec->fd_in = open(a_tkn->next->value, O_RDONLY);
		if (exec->fd_out > 1 && (a_tkn->type == REDIRECT_OUTPUT \
		|| a_tkn->type == REDIRECT_APPEND))
			close (exec->fd_out);
		if (a_tkn->type == REDIRECT_OUTPUT)
			exec->fd_out = open(a_tkn->next->value, \
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (a_tkn->type == REDIRECT_APPEND)
			exec->fd_out = open(a_tkn->next->value, \
			O_WRONLY | O_APPEND, 0644);
		a_tkn = a_tkn->next;
	}
}
