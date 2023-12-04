/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:37:30 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/12/04 17:25:30 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../executor/header/eminishell.h"

/*
*	Retorna -1 en caso de error
*/
int	ft_expander(t_parser *tools, int index, char **str_iter)
{
	char	*str;

	str = tools->input;
	if (!ft_is_operator(tools, index))
	{
		tools->expander = 1;
		if (str[index + 1] && str[index + 1] == '$')
			index = ft_getpid(tools, index);
		else if (str[index + 1] == '?')
			index = ft_getstatus(tools, index);
		else if (ft_isalnum(str[index + 1]) || str[index + 1] == '_')
			index = ft_expand_env(tools, index);
		else
			index++;
	}
	else
		index = ft_not_expand(tools, index);
	*str_iter = tools->input;
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

/*
*	Retorna -1 en caso de error
*/
int	ft_getstatus(t_parser *tools, int index)
{
	if (ft_tr_status(tools, index) == -1)
	{
		free(tools->input);
		tools->input = NULL;
		return (-1);
	}
	return (index);
}

/*
* Retorna -1 en caso de error
*/
int	ft_getpid(t_parser *tools, int index)
{
	tools->input = ft_createpid(tools->input, index);
	if (tools->input == NULL)
		return (-1);
	return (index);
}

/*
*	Retorna -1 en caso de error
*/
int	ft_expand_env(t_parser *tools, int index)
{
	int	i_env;

	i_env = ft_tr_env(tools, index);
	if (i_env == -1)
	{
		free(tools->input);
		tools->input = NULL;
		return (-1);
	}
	if (i_env == 0)
		tools->not_increment = 1;
	else
		tools->not_increment = 0;
	return (index + i_env);
}
