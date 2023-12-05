/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:17:59 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/12/05 18:26:38 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/eminishell.h"

void	ft_solo_wait(t_mini *mini)
{
	int	status;

	wait(&status);
	if (mini->status == 0)
		mini->status = ft_wait_status(status);
}

void	ft_pipe_wait(t_mini *mini)
{
	int	status;
	int	n;

	n = mini->pipe_n;
	while (n >= 0)
	{
		wait(&status);
		if (mini->pipe_status == 0 && mini->status == 0 && status != 13)
			mini->status = ft_wait_status(status);
		--n;
	}
}

int	ft_wait_status(int i)
{
	while (i > 255)
		i = i / 256;
	while (i < 0)
		i = i + 256;
	return (i);
}

char	*ft_join_n(char *ret, char *add, char *s_add)
{
	ret = ft_strfjoin(ret, add);
	ret = ft_strfjoin(ret, s_add);
	return (ret);
}

int	ft_error_cmd(t_mini *mini, char *str, int in, int out)
{
	mini->status = 1;
	if (in == -2 || out == -2)
		ft_print_err("minishell: ", str, ": Permission denied");
	else if (in == -1 || out == -1 || mini->flag_path == -1)
		ft_print_err("minishell: ", str, ": No such file or directory");
	else
	{
		mini->status = 127;
		if (!str)
			ft_print_err("minishell: : command not found", NULL, NULL);
		else
			ft_print_err("minishell: ", str, ": command not found");
	}
	mini->pipe_status++;
	return (0);
}
