/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:50:28 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/12/16 11:23:48 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/eminishell.h"

int	ft_export(t_mini *mini, t_exec *exec)
{
	t_tokens	*tkn;
	int			i;

	if (ft_strlen(exec->cmd_mtx[0]) != 6)
		return (2);
	tkn = mini->tk_lst->next;
	i = 0;
	while (tkn)
	{
		if (tkn->type == PIPE)
			break ;
		if (tkn->type == ARGUMENT)
			if (ft_export_more_args(mini, tkn->value) == 5)
				return (5);
		tkn = tkn->next;
		i = 1;
	}
	if (i == 1)
		return (0);
	if (ft_print_export(mini, exec->fd_out) == -1)
		return (-1);
	return (0);
}

int	ft_export_more_args(t_mini *mini, char *arg)
{
	int		i;

	i = 0;
	if (!arg[i])
	{
		mini->status = 1;
		ft_print_err("minishell: export: `", arg, "': not a valid identifier");
		return (5);
	}
	while (arg[i])
	{
		if (i > 0 && arg[i] == '=')
			break ;
		if (arg[i] != '_' && (ft_isalnum(arg[i]) == 0 || \
		(i == 0 && ft_isalpha(arg[i]) == 0)))
		{
			mini->status = 1;
			ft_print_err("minishell: export: `", arg, \
			"': not a valid identifier");
			return (0);
		}
		i++;
	}
	ft_change_env_var(mini, arg, 0);
	return (0);
}

int	ft_print_export(t_mini *mini, int out_fd)
{
	char		*str_exp;
	int			*used;

	used = malloc(sizeof(int *));
	if (!used)
		return (-1);
	used[0] = '\0';
	str_exp = ft_strdup("");
	if (mini->env[1] && !mini->env[2])
		str_exp = ft_str_construct(0, mini->env, str_exp);
	else if (mini->env[1])
		str_exp = ft_orden(mini->env, 0, str_exp, used);
	ft_putstr_fd(str_exp, out_fd);
	free(str_exp);
	return (0);
}
