/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:37:30 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/10/05 11:51:27 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_expander(t_parser *tools, int index)
{
	char	*str;

	str = tools->input;
	if (!ft_is_operator(tools, index))
	{
		if (str[index + 1] && str[index + 1] == '$')
			index = ft_getpid(tools, index);
		else if (str[index + 1] == '?')
			index = ft_getstatus(tools, index);
		else if (ft_isalnum(str[index + 1]) || str[index + 1] == '_')
			index = ft_expand_env(tools, index);
	}
	else
		index++;
	return (index);
}

char	*ft_get_env(char *str, int index)
{
	int		i;
	char	*env;

	if (str[index] == '$')
		index++;
	i = 0;
	while (str[index + i] && (ft_isalnum(str[index + i])
			|| str[index + i] == '_'))
		i++;
	env = ft_substr(str, index, i);
	if (env == NULL)
		return (NULL);
	return (env);
}

int	ft_getstatus(t_parser *tools, int index)
{
	if (ft_tr_status(tools, index) == 0)
	{
		free(tools->input);
		tools->input = NULL;
		return (0);
	}
	return (index);
}

int	ft_getpid(t_parser *tools, int index)
{
	tools->input = ft_createpid(tools->input, index);
	return (index);
}

int	ft_expand_env(t_parser *tools, int index)
{
	int	i_env;

	i_env = ft_tr_env(tools, index);
	if (i_env == -1)
	{
		free(tools->input);
		tools->input = NULL;
		return (0);
	}
	return (index + i_env);
}