/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_solo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:56:23 by nacho             #+#    #+#             */
/*   Updated: 2023/10/17 13:20:50 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eminishell.h"

int	ft_preprocess_solo(t_aux *aux)
{
	t_node	*aux_tkn;
	t_exec	*exec;

	exec = malloc(sizeof(t_exec *));
	if (!exec)
		return (NULL);
	aux_tkn = aux->first_token;
	exec->fd_in = 0;
	exec->fd_out = 1;
	while (aux_tkn)
	{
		ft_in_out_type(aux_tkn, exec);
		aux_tkn = aux_tkn->next_token;
	}
	aux_tkn = aux->first_token;
	while (aux_tkn)
	{
		if (aux_tkn->class == COMMAND)
			exec = ft_init_exec(aux_tkn, aux->env);
		aux_tkn = aux_tkn->next_token;
	}
	ret = ft_builtin_check(exec);
	if (ret == 2)
	{
		if (exec->path == NULL)
			ft_error_cmd(exec->cmd_mtx[0]);
		else 
			ft_exec_solo(aux, exec);
	}
	return (ret);
}

void	ft_in_out_type(t_node *token, t_exec *exec)
{
	if (token->type == HERE_DOC)
	{
		close(exec->fd_in);
		exec->fd_in = here_doc(token->content);
	}
	if (token->type == REDIRECT_INPUT)
	{
		close(exec->fd_in);
		exec->fd_in = open(token->content, O_RDONLY);
	}
	if (token->type == REDIRECT_OUTPUT)
	{
		close (exec->fd_out);
		exec->fd_out = open(token->content, \
		O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
}

pid_t	*ft_exec_solo(char **env, t_exec *exec)
{
	pid_t	*pidc;

	pidc = fork();
	if (prg->pidc == -1)
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
	ft_free_exec(exec);
	return (pidc);
}

void	ft_free_exec(t_exec *exec)
{
	close (exec->fd_in);
	close (exec->fd_out);
	free(exec->path);
	ft_free_mtx(exec->cmd_mtx);
	free(exec);
}

t_exec	*ft_init_exec(t_node *token, char **env)
{
	t_node	*aux;
	char	*aux_cmd;
	t_exec	*exec;

	exec->path = ft_find_path(env, token->content);
	aux = token;
	aux_cmd = ft_strdup("");
	while (aux && (aux->class == COMMAND || aux->class == ARGUMENT))
	{
		aux_cmd = ft_strfjoin(aux_cmd, aux->content);
		aux_cmd = ft_strfjoin(aux_cmd, " ");
		aux = aux->next_token;
	}
	exec->cmd_mtx = ft_split(aux_cmd, " ");
	free(aux_cmd);
	return (exec);
}

char	*ft_find_path(char **envp, char *cmd)
{
	char	**pos_paths;
	char	*path;
	int		i;

	i = 0;
	if (envp == NULL)
		return (NULL);
	path = cmd;
	if (ft_strrchr(cmd, '/') == NULL)
	{
		while (envp[i])
		{
			if (ft_strnstr(envp[i], "PATH", 5) && ft_strlen(envp[i]) > 7)
			{
				pos_paths = ft_split(envp[i] + 6, ':');
				path = ft_no_path(cmd, pos_paths);
				ft_free_mtx(pos_paths);
				break ;
			}
			i++;
		}
	}
	else if (access(path, F_OK) != 0)
		return (NULL);
	return (path);
}

char	*ft_no_path(char *cmd, char **pos_paths)
{
	int		i;
	char	*path;

	i = 0;
	while (pos_paths[i])
	{
		path = ft_strjoin(pos_paths[i], "/");
		path = ft_strfjoin(path, cmd);
		if (access(path, F_OK) == 0)
		{
			i = -1;
			break ;
		}
		free (path);
		i++;
	}
	if (i != -1)
		path = NULL;
	return (path);
}
