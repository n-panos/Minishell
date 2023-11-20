/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:17:59 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/20 10:34:48 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/eminishell.h"

void	ft_solo_wait(t_mini *mini, t_exec *exec)
{
	int	status;

	wait(&status);
	mini->status = status;
	ft_free_exec(exec);
}

void	ft_pipe_wait(t_mini *mini)
{
	int	status;
	int	n;
	int	flag;

	n = mini->cmd_n;
	flag = 0;
	if (mini->status == 0)
		flag = 1;
	while (n > 0)
	{
		if (flag == 1)
			mini->status = status;
		wait(&status);
		n--;
	}
}

int	ft_wait_status(int i)
{
	if (i > 255)
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
	if (mini->flag_path == -1 || in == -1 || out == -1)
	{
		mini->status = 1;
		printf("minishell: %s: No such file or directory\n", str);
	}
	else
	{
		mini->status = 127;
		printf("minishell: %s: command not found\n", str);
	}
	return (0);
}
