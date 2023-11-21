/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:17:59 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/21 13:23:29 by nacho            ###   ########.fr       */
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

	n = mini->cmd_n;
	while (n > 0)
	{
		wait(&status);
		//mini->status = ft_wait_status(status);
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
		printf("minishell: %s: Permission denied\n", str);
	else if (in == -1 || out == -1)
		printf("minishell: %s: No such file or directory\n", str);
	else if (mini->flag_path == -1)	
		printf("minishell: %s: No such file or directory\n", str);
	else
	{
		mini->status = 127;
		printf("minishell: %s: command not found\n", str);
	}
	return (0);
}
