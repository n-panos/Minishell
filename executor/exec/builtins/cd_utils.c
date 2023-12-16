/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 09:50:11 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/12/16 10:33:44 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/eminishell.h"

int	ft_null_getcwd(t_mini *mini)
{
	char	*aux;
	char	*aux_h;
	int		i;

	aux = ft_get_env_var(mini->env, "PWD");
	i = ft_strlen(aux);
	if (aux[-1 + i] == '.' && aux[-2 + i] == '.')
	{
		aux_h = ft_get_env_var(mini->env, "HOME");
		chdir(++aux_h);
		aux_h = ft_strjoin("PWD=", aux_h);
		ft_change_env_var(mini, aux_h, 0);
		ft_change_old_pwd(mini, ++aux);
		return (free(aux_h), 0);
	}
	aux = ft_strjoin("PWD", aux);
	aux = ft_strfjoin(aux, "/..");
	ft_change_env_var(mini, aux, 0);
	ft_print_err("cd: error retrieving current directory: getcwd: cannot \
	access parent directories: No such file or directory", NULL, NULL);
	return (free(aux), 0);
}
