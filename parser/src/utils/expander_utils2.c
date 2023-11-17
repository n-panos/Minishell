/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:45:59 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/11/17 19:22:18 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../executor/header/eminishell.h"

/*
*	Retorna 1 si el argumento es un delimitador del heredoc, y no expande
*/
int	ft_is_operator(t_parser *tools, int index)
{
	int		i;
	char	*str;

	i = index - 1;
	str = tools->input;
	while (i >= 0 && (str[i] == ' ' || str[i] == '\t'))
		i--;
	if (str[i] == '<')
	{
		i--;
		if (i >= 0 && str[i] == '<')
			return (1);
	}
	return (0);
}

/*
*	Retorna el index
*/
int	ft_not_expand(t_parser *tools, int index)
{
	int	i;

	i = index;
	while (tools->input[i])
	{
		if (ft_strchr(DELIMITERS, tools->input[i]))
			break ;
		else if (tools->input[i] == ' ' || tools->input[i] == '\0')
			break ;
		i++;
	}
	return (i);
}

static void	ft_free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

char	*get_env(char *env, t_parser *tools, int *v2)
{
	char	*result;
	char	**envp;
	int		i;

	*v2 = 0;
	i = -1;
	while (tools->env[++i])
	{
		envp = ft_split(tools->env[i], '=');
		if (ft_strncmp(envp[0], env, ft_strlen(env)) == 0
			&& ft_strlen(env) == ft_strlen(envp[0]))
		{
			if (!envp[1])
				return (ft_free_split(envp), NULL);
			else
				result = ft_strdup(envp[1]);
			break ;
		}
		ft_free_split(envp);
	}
	if (tools->env[i] == NULL)
		return (NULL);
	*v2 = 1;
	ft_free_split(envp);
	return (result);
}

int	ft_three_str(t_truncate *tr)
{
	int	sum;

	tr->tmp = ft_strjoin(tr->str1, tr->var2);
	tr->result = ft_strjoin(tr->tmp, tr->str2);
	sum = ft_strlen(tr->var2) - 1;
	return (sum);
}
