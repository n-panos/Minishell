/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_more.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:09:25 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/15 14:47:41 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/eminishell.h"

void	ft_waiting(int n, int *fd)
{
	int	status;

	if (fd[0] > 1)
		close(fd[0]);
	free(fd);
	while (n > 0)
	{
		wait(&status);
		n--;
	}
	signal_handler(ITERATIVE);
}

char	*ft_join_n(char *ret, char *add, char *s_add)
{
	ret = ft_strfjoin(ret, add);
	ret = ft_strfjoin(ret, s_add);
	return (ret);
}

int	ft_error_cmd(t_mini *mini, char *str, int in, int out)
{
	if (in == -1 || out == -1)
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

char	*ft_get_shlvl(char **env, int flag)
{
	char	**aux;
	char	*lvl;
	int		i;

	i = 0;
	lvl = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "SHLVL", 5) == 0)
		{
			aux = ft_split(env[i], '=');
			if (ft_all_isdigit(aux[1]) == 1)
			{
				i = ft_atoi(aux[1]) + flag;
				lvl = ft_itoa(i);
			}
			ft_mtx_free(aux);
			break ;
		}
		i++;
	}
	return (lvl);
}
