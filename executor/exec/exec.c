/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:16:49 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/23 09:37:37 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/eminishell.h"

// return es -1 si hubo algun error de ejecucion, 0 si ejecuto bien, 
// 1 si viene del comando exit y hay que cerrar la consola

int	ft_execute(t_mini *mini)
{
	int			ret;

	ret = 0;
	mini->status = 0;
	mini->pipe_status = 0;
	if (ft_is_env_i_mini(mini) == 0)
		return (ret);
	else if (mini->cmd_n == 0)
		ret = ft_no_cmd(mini);
	else if (mini->cmd_n == 1)
		ret = ft_preprocess_solo(mini);
	else if (mini->cmd_n > 1)
		ret = ft_preprocess_pipe(mini, 0);
	return (ret);
}

// return 2 si no ha hecho nada, return 0 sin problema, 
// 1 es exit, -1 error

int	ft_no_cmd(t_mini *mini)
{
	t_tokens	*atkn;
	int			i;

	i = 0;
	atkn = mini->tk_lst;
	while (atkn->next)
	{
		if (atkn->type == HEREDOC)
			close(here_doc(atkn->next->value));
		if (atkn->type == REDIRECT_OUTPUT)
			open(atkn->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (i > 1)
			close (i);
		atkn = atkn->next;
	}
	return (0);
}

int	ft_is_env_i_mini(t_mini *mini)
{
	t_tokens	*tkn;
	int			status;
	char		**empty_env;
	t_exec		*exec;

	tkn = mini->tk_lst;
	if (ft_cmp_mini(tkn) == 0)
	{
		if (mini->flag_path == -1)
			return (1);
		empty_env = ft_split("", ' ');
		exec = ft_i_mini_util(mini, tkn);
		signal_off();
		ft_minishell_exec(empty_env, exec);
		wait(&status);
		mini->status = ft_wait_status(status);
		ft_mtx_free(empty_env);
		ft_free_exec(mini, exec);
		signal_handler(ITERATIVE);
		return (0);
	}
	return (1);
}

int	ft_cmp_mini(t_tokens *tkn)
{
	if (tkn && ft_strncmp(tkn->value, "env", 3) == 0 && \
	ft_strlen(tkn->value) == 3)
	{
		tkn = tkn->next;
		if (tkn && ft_strncmp(tkn->value, "-i", 2) == 0 && \
		ft_strlen(tkn->value) == 2)
		{
			tkn = tkn->next;
			if (tkn && ft_strncmp(tkn->value, "./minishell", 11) == 0 && \
			ft_strlen(tkn->value) == 11)
			{
				return (0);
			}
		}
	}
	return (1);
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
