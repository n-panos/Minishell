/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erick <erick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:16:31 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/11/07 15:19:14 by erick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../executor/header/eminishell.h"

static t_truncate	*ft_createstrpid(char *str, int index)
{
	t_truncate	*tr;

	tr = malloc(sizeof(t_truncate));
	if (tr == NULL)
		return (NULL);
	tr->pid = getpid();
	tr->var1 = ft_itoa(tr->pid);
	tr->str1 = ft_substr(str, 0, index);
	tr->str2 = ft_substr(str, index + 2, ft_strlen(str));
	if (tr->var1 == NULL || tr->str1 == NULL || tr->str2 == NULL)
	{
		free(tr->var1);
		free(tr->str1);
		free(tr->str2);
		return (NULL);
	}
	tr->tmp = ft_strjoin(tr->str1, tr->var1);
	free(tr->str1);
	free(tr->var1);
	if (tr->tmp == NULL)
		return (NULL);
	tr->result = ft_strjoin(tr->tmp, tr->str2);
	free(tr->tmp);
	free(tr->str2);
	return (tr);
}

char	*ft_createpid(char *str, int index)
{
	t_truncate	*tr;
	char		*result;

	tr = ft_createstrpid(str, index);
	if (tr == NULL)
		return (NULL);
	result = tr->result;
	free(tr);
	free(str);
	return (result);
}

/*
*	Retorna -1 en caso de error
*/
int	ft_tr_status(t_parser *tools, int index)
{
	t_truncate	*tr;

	tr = malloc(sizeof(t_truncate));
	if (tr == NULL)
		return (-1);
	tr->str1 = ft_substr(tools->input, 0, index);
	tr->str2 = ft_substr(tools->input, index + 2, ft_strlen(tools->input));
	tr->var1 = ft_itoa(tools->status);
	if (!tr->str1 || !tr->str2 || !tr->var1)
		return (ft_free_tr(tr), -1);
	tr->tmp = ft_strjoin(tr->str1, tr->var1);
	if (tr->tmp == NULL)
		return (ft_free_tr(tr), -1);
	tr->result = ft_strjoin(tr->tmp, tr->str2);
	if (tr->result == NULL)
		return (ft_free_tr(tr), -1);
	free(tools->input);
	tools->input = tr->result;
	ft_free_tr(tr);
	return (index);
}

int	ft_tr_env(t_parser *tools, int index)
{
	t_truncate	*tr;
	int			sum;

	tr = malloc(sizeof(t_truncate));
	if (tr == NULL)
		return (-1);
	sum = 0;
	tr->var1 = ft_get_env(tools->input, index);
	tr->var2 = get_env(tr->var1, tools, &tr->v2);
	tr->str1 = ft_substr(tools->input, 0, index);
	tr->str2 = ft_substr(tools->input, index + ft_strlen(tr->var1) + 1,
			ft_strlen(tools->input));
	if (tr->var2 == NULL)
		tr->result = ft_strjoin(tr->str1, tr->str2);
	else
	{
		tr->tmp = ft_strjoin(tr->str1, tr->var2);
		tr->result = ft_strjoin(tr->tmp, tr->str2);
		sum = ft_strlen(tr->var2) - 1;
	}
	if (tr->result == NULL)
		return (ft_free_tr(tr), -1);
	free(tools->input);
	tools->input = tr->result;
	return (ft_free_tr(tr), sum);
}

void	ft_free_tr(t_truncate *tr)
{
	if (tr->str1 != NULL)
		free(tr->str1);
	if (tr->str2 != NULL)
		free(tr->str2);
	if (tr->tmp != NULL)
		free(tr->tmp);
	if (tr->var1 != NULL)
		free(tr->var1);
	if (tr->v2)
		free(tr->var2);
	free(tr);
}
