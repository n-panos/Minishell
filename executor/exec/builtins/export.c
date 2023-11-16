/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:50:28 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/16 09:34:07 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/eminishell.h"

int	ft_export(t_mini *mini, char **cmd_mtx)
{
	char	*str_exp;
	int		*used;
	int		i;

	if (ft_strlen(cmd_mtx[0]) != 6)
		return (2);
	i = 1;
	while (cmd_mtx[i])
	{
		//ft_funcion de quitar tabs y espacios
		if (i >= 1)
			ft_export_more_args(mini, cmd_mtx[i]);
		i++;
	}
	if (i > 1)
		return (0);
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
