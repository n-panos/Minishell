/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struc_ex_inits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 09:39:40 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/24 11:01:54 by ipanos-o         ###   ########.fr       */
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
		if (tkn->type == PIPE)
			break ;
		if (tkn->type == COMMAND)
		{
			ret = ft_init_exec(tkn, mini, in, out);
			if (ret == NULL)
				mini->status = 12;
			break ;
		}
		tkn = tkn->next;
	}
	return (ret);
}

t_exec	*ft_init_exec(t_tokens *token, t_mini *mini, int in, int out)
{
	t_tokens	*aux;
	char		*aux_cmd;
	t_exec		*exec;

	exec = ft_calloc(1, sizeof(t_exec));
	if (!exec)
		return (NULL);
	exec->fd_in = in;
	exec->fd_out = out;
	if (ft_builtin_path(token->value) == 0)
		exec->path = ft_find_path(mini->env, token->value, mini->flag_path);
	else
		exec->path = NULL;
	aux = token;
	aux_cmd = ft_strdup("");
	while (aux && (aux->type == COMMAND || aux->type == ARGUMENT))
	{
		aux_cmd = ft_join_n(aux_cmd, aux->value, " ");
		aux = aux->next;
	}
	exec->cmd_mtx = ft_split(aux_cmd, ' ');
	free(aux_cmd);
	exec->cmd_mtx = ft_has_empty(token, exec->cmd_mtx);
	return (exec);
}

char	**ft_has_empty(t_tokens *minitkn, char **mtx)
{
	t_tokens	*tkn;

	tkn = minitkn;
	while (tkn)
	{
		if (tkn->type == PIPE)
			break ;
		if (tkn->value[0] == '\0' && ft_mtx_line_cnt(mtx) > 0)
			return (ft_remove_empty(mtx));
		tkn = tkn->next;
	}
	return (mtx);
}

char	**ft_remove_empty(char **mtx)
{
	char	**new_mtx;
	int		i;

	new_mtx = (char **)malloc((ft_mtx_line_cnt(mtx) + 2) * sizeof(char));
	new_mtx[0] = ft_strdup(mtx[0]);
	new_mtx[1] = ft_strdup("");
	i = 2;
	while (mtx[i - 1])
	{
		new_mtx[i] = ft_strdup(mtx[i - 1]);
		++i;
	}
	new_mtx[i] = NULL;
	ft_mtx_free(mtx);
	return (new_mtx);
}

t_exec	*ft_i_mini_util(t_mini *mini, t_tokens *tkn)
{
	char	str[FILENAME_MAX];
	t_exec	*exec;

	exec = ft_add_cmd(tkn, mini, 0);
	if (!exec)
		return (NULL);
	free(exec->path);
	getcwd(str, sizeof(str));
	exec->path = ft_strjoin(str, "/minishell");
	ft_mtx_free(exec->cmd_mtx);
	exec->cmd_mtx = ft_split("./minishell", ' ');
	return (exec);
}
