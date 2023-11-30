/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 09:50:11 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/30 11:39:37 by ipanos-o         ###   ########.fr       */
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
		ft_change_env_var(mini, aux_h);
		ft_change_old_pwd(mini, ++aux);
		return (free(aux_h), 0);
	}
	aux = ft_strjoin("PWD", aux);
	aux = ft_strfjoin(aux, "/..");
	ft_change_env_var(mini, aux);
	printf("cd: error retrieving current directory: getcwd: cannot ");
	printf("access parent directories: No such file or directory\n");
	return (free(aux), 0);
}
