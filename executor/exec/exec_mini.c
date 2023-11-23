#include "../header/eminishell.h"

int	ft_is_minishell(t_mini *mini, t_exec *exec)
{
	char	str[FILENAME_MAX];
	// char	*prev_shlvl;
	int		status;

	if (!exec->cmd_mtx[0] || ft_strncmp(exec->cmd_mtx[0], "./minishell", 11) \
	!= 0 || ft_strlen(exec->cmd_mtx[0]) != 11)
		return (2);
	// prev_shlvl = ft_strjoin("SHLVL", ft_get_env_var(mini->env, "SHLVL"));
	// ft_change_shlvl(mini, 1);
	free(exec->path);
	getcwd(str, sizeof(str));
	exec->path = ft_strjoin(str, "/minishell");
	signal_off();
	ft_minishell_exec(mini->env, exec);
	wait(&status);
	mini->status = ft_wait_status(status);
	// ft_change_env_var(mini, prev_shlvl);
	// free(prev_shlvl);
	return (0);
}

int	ft_is_env_i_mini(t_mini *mini)
{
	t_tokens	*tkn;
	int			status;
	char		**empty_env;
	t_exec		*exec;

	tkn = mini->tk_lst;
	if (ft_cmp_mini(tkn) == 0)
	{
		if (mini->flag_path == -1)
			return (1);
		empty_env = ft_split("", ' ');
		exec = ft_i_mini_util(mini, tkn);
		signal_off();
		ft_minishell_exec(empty_env, exec);
		wait(&status);
		mini->status = ft_wait_status(status);
		ft_mtx_free(empty_env);
		ft_free_exec(mini, exec);
		signal_handler(ITERATIVE);
		return (0);
	}
	return (1);
}

int	ft_cmp_mini(t_tokens *tkn)
{
	if (tkn && ft_strncmp(tkn->value, "env", 3) == 0 && \
	ft_strlen(tkn->value) == 3)
	{
		tkn = tkn->next;
		if (tkn && ft_strncmp(tkn->value, "-i", 2) == 0 && \
		ft_strlen(tkn->value) == 2)
		{
			tkn = tkn->next;
			if (tkn && ft_strncmp(tkn->value, "./minishell", 11) == 0 && \
			ft_strlen(tkn->value) == 11)
			{
				return (0);
			}
		}
	}
	return (1);
}

void	ft_minishell_exec(char **env, t_exec *exec)
{
	pid_t	pidc;

	pidc = fork();
	if (pidc == -1)
		exit(EXIT_FAILURE);
	if (pidc == 0)
		ft_executing_solo_cmds(env, exec);
}
