/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:17:59 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/11 18:18:29 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/eminishell.h"

int	ft_error_cmd(t_mini *mini, char *str, int in, int out)
{
	if (in == -1 || out == -1)
	{
		mini->status = 1;
		printf("minishell: %s: No such file or directory\n", str);
	}
	else
	{
		mini->status = 127;
		printf("minishell: %s: command not found\n", str);
	}
	return (0);
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
		aux_cmd = ft_strfjoin(aux_cmd, aux->value);
		aux_cmd = ft_strfjoin(aux_cmd, " ");
		aux = aux->next;
	}
	exec->cmd_mtx = ft_split(aux_cmd, ' ');
	free(aux_cmd);
	return (exec);
}

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

char	*ft_find_path(char **envp, char *cmd)
{
	char	**pos_paths;
	char	*path;
	int		i;

	i = 0;
	if (envp == NULL || cmd == NULL)
		return (NULL);
	path = ft_strdup(cmd);				 // ERICK
	// path = cmd;
	if (ft_strrchr(cmd, '/') == NULL)
	{
		while (envp[i])
		{
			if (ft_strnstr(envp[i], "PATH", 5) && ft_strlen(envp[i]) > 7)
			{
				free(path); 			// ERICK
				pos_paths = ft_split(envp[i] + 6, ':');
				path = ft_no_path(cmd, pos_paths);
				ft_mtx_free(pos_paths);
				break ;
			}
			i++;
		}
		if (envp[i] == NULL)			//ERICK
			return (free(path), NULL);	//ERICK
	}
	else if (access(path, F_OK) != 0)
		return (free(path), NULL);
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
