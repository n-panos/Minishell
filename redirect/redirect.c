/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:00:56 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/20 13:00:51 by nacho            ###   ########.fr       */
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
		if (ret > 1 && (atkn->type == REDIRECT_OUTPUT \
		|| atkn->type == REDIRECT_APPEND))
			close(ret);
		if (atkn->type == REDIRECT_OUTPUT)
		{
			ret = open(atkn->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (atkn->prev->type == REDIRECT_INPUT)
				close(ret);
		}
		else if (atkn->type == REDIRECT_APPEND)
			ret = open(atkn->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (ret == -1)
			return (ft_file_exists(mini, atkn->next->value), ret);
		atkn = atkn->next;
	}
	return (ret);
}

/*int	check_out(t_mini *mini, t_tokens *tkn)
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
		if (ret > 1 && (atkn->type == REDIRECT_OUTPUT \
		|| atkn->type == REDIRECT_APPEND))
			close(ret);
		if (atkn->type == REDIRECT_OUTPUT)
			ret = open(atkn->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (atkn->type == REDIRECT_APPEND)
			ret = open(atkn->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (ret == -1)
			return (ft_error_cmd(mini, atkn->next->value, 0, -1));
		atkn = atkn->next;
	}
	return (ret);
}*/

int	check_in(t_mini *mini, t_tokens *tkn, int in)
{
	t_tokens	*atkn;
	int			ret;

	atkn = tkn;
	ret = in;
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
			ret = here_doc(atkn->next->value);
		if (ret == -1)
			return (ft_file_exists(mini, atkn->next->value), ret);
		atkn = atkn->next;
	}
	return (ret);
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

//devuelve -1 si no existe
//devuelve 0 si existe