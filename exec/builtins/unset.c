/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:37:50 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/10/19 13:22:09 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eminishell.h"

void		ft_env_delete(t_mini *mini, int erase);
static int	ft_search_igual(char *str);
void		ft_env_rm(t_mini *mini, char *str);

int	ft_unset(t_mini *mini, char *str)
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
			ft_env_rm(mini, aux[i]);
		i++;
	}
	if (i == 1)
		printf("unset: not enough arguments\n");
	return (0);
}

void	ft_env_delete(t_mini *mini, int erase)
{
	char	*aux;
	int		i;

	i = 0;
	aux = ft_strdup("");
	while (mini->env[i])
	{
		if (i == erase)
			i++;
		else
		{
			aux = ft_strfjoin(aux, mini->env[i]);
			aux = ft_strfjoin(aux, "\n");
			i++;
		}
	}
	mini->env = ft_split(aux, '\n');
	free(aux);
}

void	ft_env_rm(t_mini *mini, char *str)
{
	int		i;
	int		len;

	i = 0;
	while (mini->env[i])
	{
		len = ft_search_igual(mini->env[i]);
		if (ft_strncmp(mini->env[i], str, len) == 0)
		{
			ft_env_delete(mini, i);
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