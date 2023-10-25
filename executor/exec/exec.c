/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:11:50 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/10/25 13:08:18 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/eminishell.h"

// return es -1 si hubo algun error de ejecucion, 0 si ejecuto bien, 
// 1 si viene del comando exit y hay que cerrar la consola

int	ft_execute(t_mini *mini)
{
	int			ret;
	//t_tokens	*atkn;
	//int			i;

	ret = 0;
	/*i = 0;
	atkn = mini->tk_lst;
	while (atkn)
	{
		close(i);
		i = is_valid_redi_here(atkn);
		if (i == -1)
			return (0);
		atkn = atkn->next;
	}*/
	if (mini->cmd_n == 0)
		ret = ft_no_cmd(mini);
	if (mini->cmd_n == 1)
		ret = ft_preprocess_solo(mini);
	else if (mini->pipe_n > 1)
		ret = ft_preprocess_pipe(mini);
	return (ret);
}

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

//-1 mensaje de error, 0 es ok,

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

/*int	is_valid_redi_here(t_tokens *tkn)
{
	if (tkn->type == REDIRECT_INPUT || tkn->type == REDIRECT_OUTPUT || \
	tkn->type == REDIRECT_APPEND || tkn->type == HEREDOC)
	{
		if (!tkn->next)
			printf("minishell: syntax error near unexpected token `newline'");
		else if (tkn->type == HEREDOC && tkn->next->type == DELIMITER)
			return (here_doc(tkn->next->value));
		else if (tkn->type == REDIRECT_INPUT || tkn->next->type == ARGUMENT)
			return (open(tkn->next->value, O_RDONLY));
		else if (tkn->next->type == ARGUMENT)
			return (0);
		else
			printf("minishell: syntax error near unexpected token `%s'", \
			tkn->next->value);
		return (-1);
	}
	return (0);
}*/
