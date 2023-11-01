/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:17:59 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/01 11:22:16 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/eminishell.h"

void	ft_error_cmd(char *str)
{
	ft_putstr_fd("zsh: command not found: ", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("\n", 1);
}

t_exec	*ft_init_exec(t_tokens *token, char **env, int in, int out)
{
	t_tokens	*aux;
	char		*aux_cmd;
	t_exec		*exec;

	exec = ft_calloc(1, sizeof(t_exec));
	if (!exec)
		exit(EXIT_FAILURE);
	exec->fd_in = in;
	exec->fd_out = out;
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

t_exec	*ft_add_cmd(t_tokens *tkn, char **env, int in)
{
	t_exec	*ret;
	int		out;

	in = ft_check_in(tkn, in);
	out = ft_check_out(tkn);
	ret = NULL;
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

char	*ft_find_path(char **envp, char *cmd)
{
	char	**pos_paths;
	char	*path;
	int		i;

	i = 0;
	if (envp == NULL || cmd == NULL)
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
				ft_mtx_free(pos_paths);
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
