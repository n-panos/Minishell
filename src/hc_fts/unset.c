/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:37:50 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/09/29 10:35:24 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eminishell.h"

void		ft_env_delete(t_prg *prg, int erase);
static int	ft_search_igual(char *str);
void		ft_env_rm(t_prg *prg, char *str);

int	ft_exec_unset(t_prg *prg, char *str)
{
	char	**aux;
	int		i;

	if (str == NULL)
		return (0);
	aux = ft_split(str, ' ');
	i = 0;
	while (aux[i])
	{
		if (i >= 1)
			ft_env_rm(prg, aux[i]);
		i++;
	}
	if (i == 1)
		printf("unset: not enough arguments\n");
	return (0);
}

void	ft_env_delete(t_prg *prg, int erase)
{
	char	*aux;
	int		i;

	i = 0;
	aux = ft_strdup("");
	while (prg->env[i])
	{
		if (i == erase)
			i++;
		else
		{
			aux = ft_strfjoin(aux, prg->env[i]);
			aux = ft_strfjoin(aux, "\n");
			i++;
		}
	}
	prg->env = ft_split(aux, '\n');
	free(aux);
}

void	ft_env_rm(t_prg *prg, char *str)
{
	int		i;
	int		len;

	i = 0;
	while (prg->env[i])
	{
		len = ft_search_igual(prg->env[i]);
		if (ft_strncmp(prg->env[i], str, len) == 0)
		{
			ft_env_delete(prg, i);
			break ;
		}
		i++;
	}
}

static int	ft_search_igual(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}