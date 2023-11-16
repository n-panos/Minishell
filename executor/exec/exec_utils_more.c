/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_more.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:09:25 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/16 14:34:17 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/eminishell.h"

void	ft_waiting(t_mini *mini, int *fd)
{
	int	status;
	int	n;
	int	flag;

	if (fd[0] > 1)
		close(fd[0]);
	free(fd);
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

void	ft_pipe_odd(t_mini *mini, t_tokens *atkn, int aux_fd)
{
	t_exec	*odd;

	odd = ft_add_cmd(atkn, mini, aux_fd);
	if (odd)
		ft_exec_type(mini, odd, odd->fd_in, odd->fd_out);
}
