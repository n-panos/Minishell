/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:11:50 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/10/24 11:43:11 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/eminishell.h"

// return es -1 si hubo algun error de ejecucion, 0 si ejecuto bien, 
// 1 si viene del comando exit y hay que cerrar la consola

int	ft_execute(t_mini *mini)
{
	int			ret;
	t_tokens	*a_tkn;

	ret = 0;
	//if (mini->cmd_n == 0)
	//	ret = ft_no_cmd(mini);
	if (mini->cmd_n == 1)
		ret = ft_preprocess_solo(mini);
	else if (mini->cmd_n > 1)
		ret = ft_preprocess_pipe(mini);
	return (ret);
}

//-2 mensaje de error -1 no son redirect, 0 es ok, ret >1 es id pipe del heredoc

/*int	ft_no_cmd()
{
}

int	is_valid_red_here(t_tokens *tkn)
{
	t_tokens	*a_tkn;
	int			ret;

	a_tkn = tkn;
	if (a_tkn->type == REDIRECT_INPUT || a_tkn->type == REDIRECT_OUTPUT || \
	a_tkn->type == REDIRECT_APPEND || a_tkn->type == HEREDOC)
	{
		if (!a_tkn->next)
			printf("minishell: syntax error near unexpected token `newline'");
		else if (a_tkn->next->type == PIPE)
			printf("minishell: syntax error near unexpected token `|'");
		else if (a_tkn->next->type == ARGUMENT)
			return (0);
		return (-2);
	}
	if (a_tkn->type == HEREDOC && a_tkn->next->type == DELIMITER)
		close(here_doc(tkn->next->value));
	return (-1);
}*/

// return 2 si no ha hecho nada, return 0 sin problema, 
// 1 es exit, -1 error

int	ft_builtin_check(t_exec *exec, t_mini *mini)
{
	int	i;

	i = 2;
	if (ft_strncmp(exec->cmd_mtx[0], "cd", 2) == 0)
		i = ft_cd(exec->cmd_mtx);
	else if (ft_strncmp(exec->cmd_mtx[0], "echo", 4) == 0)
		i = ft_echo(exec->cmd_mtx);
	else if (ft_strncmp(exec->cmd_mtx[0], "env", 3) == 0)
		i = ft_env(mini->env, exec->cmd_mtx);
	else if (ft_strncmp(exec->cmd_mtx[0], "exit", 4) == 0)
		i = ft_exit(exec->cmd_mtx);
	// else if (ft_strncmp(exec->cmd_mtx[0], "export", 6))
	// 	i = ft_export(mini, exec->cmd_mtx);
	else if (ft_strncmp(exec->cmd_mtx[0], "pwd", 3) == 0)
		i = ft_pwd(exec->cmd_mtx);
	else if (ft_strncmp(exec->cmd_mtx[0], "unset", 5) == 0)
		i = ft_unset(mini, exec->cmd_mtx);
	return (i);
}
