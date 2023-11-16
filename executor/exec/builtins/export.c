/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:50:28 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/16 17:39:19 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/eminishell.h"

int	ft_export(t_mini *mini, char **cmd_mtx)
{
	t_tokens	*tkn;
	int			i;

	if (ft_strlen(cmd_mtx[0]) != 6)
		return (2);
	tkn = mini->tk_lst->next;
	i = 0;
	while (tkn)
	{
		ft_export_more_args(mini, tkn->value);
		tkn = tkn->next;
		i = 1;
	}
	if (i == 1)
		return (0);
	if (ft_print_export(mini) == -1)
		return (-1);
	return (0);
}

int	ft_export_more_args(t_mini *mini, char *arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		if (i > 0 && arg[i] == '=')
			break ;
		if (arg[i] != '_' && (ft_isalnum(arg[i]) == 0 || \
		(i == 0 && ft_isalpha(arg[i]) == 0)))
		{
			printf("minishell: export: `%s': not a valid identifier\n", arg);
			return (0);
		}
		i++;
	}
	ft_change_env_var(mini, arg);
	return (0);
}

int	ft_print_export(t_mini *mini)
{
	char		*str_exp;
	int			*used;

	used = malloc(sizeof(int *));
	if (!used)
		return (-1);
	used[0] = '\0';
	str_exp = ft_strdup(" ");
	str_exp = ft_orden(mini->env, 0, str_exp, used);
	printf("%s", str_exp);
	free(str_exp);
	return (0);
}
