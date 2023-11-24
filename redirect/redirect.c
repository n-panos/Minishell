/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:00:56 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/24 12:57:51 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor/header/eminishell.h"

int	check_out(t_mini *mini, t_tokens *tkn)
{
	t_tokens	*atkn;
	int			ret;

	atkn = tkn;
	ret = 1;
	while (atkn)
	{
		if (atkn->type == PIPE)
		{
			if (ret == 1)
				return (-2);
			break ;
		}
		ret = ft_out_open(atkn->type, atkn->next->value, ret, atkn->prev->type);
		if (ret == -1)
			return (ft_file_exists(mini, atkn->next->value), ret);
		atkn = atkn->next;
	}
	return (ret);
}

int	ft_out_open(t_type type, char *value, int ret, t_type prev_type)
{
	if (ret > 1 && (type == REDIRECT_OUTPUT || type == REDIRECT_APPEND))
		close(ret);
	if (type == REDIRECT_OUTPUT)
	{
		ret = open(value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (prev_type == REDIRECT_INPUT)
			close(ret);
	}
	else if (type == REDIRECT_APPEND)
		ret = open(value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (ret);
}

int	check_in(t_mini *mini, t_tokens *tkn, int in)
{
	t_tokens	*atkn;
	int			ret;

	atkn = tkn;
	ret = in;
	if (ft_only_redi(atkn) == 1)
		return (-2);
	while (atkn)
	{
		if (atkn->type == PIPE)
			break ;
		if (ret > 0 && (atkn->type == HEREDOC \
		|| atkn->type == REDIRECT_INPUT))
			close(ret);
		if (atkn->type == REDIRECT_INPUT && atkn->next->type != ARGUMENT)
			ret = in;
		else if (atkn->type == REDIRECT_INPUT)
			ret = open(atkn->next->value, O_RDONLY);
		else if (atkn->type == HEREDOC)
			ret = here_doc(atkn->next->value, STDIN_FILENO);
		if (ret == -1)
			return (ft_file_exists(mini, atkn->next->value), ret);
		atkn = atkn->next;
	}
	return (ret);
}

int	ft_only_redi(t_tokens *tkn)
{
	t_tokens	*aux;

	aux = tkn;
	while (aux)
	{
		if (aux->type == PIPE)
			break ;
		if (aux->type == COMMAND)
			return (0);
		aux = aux->next;
	}
	return (1);
}

int	ft_file_exists(t_mini *mini, char *file)
{
	char	str[FILENAME_MAX];
	char	*aux;
	int		i;

	getcwd(str, sizeof(str));
	aux = ft_strjoin(str, "/");
	aux = ft_strfjoin(aux, file);
	i = access(aux, F_OK);
	if (i == 0)
		ft_error_cmd(mini, file, -2, 0);
	else if (i == -1)
		ft_error_cmd(mini, file, -1, 0);
	free(aux);
	return (0);
}
