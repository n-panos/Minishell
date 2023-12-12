/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struc_ex_inits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 09:39:40 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/12/12 14:06:45 by ipanos-o         ###   ########.fr       */
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
	exec->cmd_mtx = ft_mini_split(token);
	return (exec);
}

char	**ft_mini_split(t_tokens *minitkn)
{
	t_tokens	*tkn;
	int			i;
	char		**mtx;

	tkn = minitkn;
	i = 1;
	while (tkn && (tkn->type == COMMAND || tkn->type == ARGUMENT \
	|| tkn->type == PIPE))
	{
		tkn = tkn->next;
		++i;
	}
	mtx = malloc(i * sizeof(char **));
	i = 0;
	tkn = minitkn;
	while (tkn && (tkn->type == COMMAND || tkn->type == ARGUMENT \
	|| tkn->type == PIPE))
	{
		mtx[i] = ft_strdup(tkn->value);
		tkn = tkn->next;
		++i;
	}
	mtx[i] = NULL;
	return (mtx);
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
