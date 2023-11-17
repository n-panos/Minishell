#include "../header/eminishell.h"

t_pipes	*ft_config_pipe(t_tokens *tkn, t_mini *mini, int in)
{
	t_pipes		*pipes;
	int			in_cmd2;

	pipes = ft_calloc(1, sizeof(t_pipes));
	if (!pipes)
		return (NULL);
	pipes->cmd1 = ft_add_cmd(tkn, mini, in);
	tkn = ft_return_pipe(tkn);
	in_cmd2 = 0;
	if (pipes->cmd1->fd_out != -2)
		in_cmd2 = -5;
	pipes->cmd2 = ft_add_cmd(tkn, mini, in_cmd2);
	if (pipes->cmd1 == NULL || pipes->cmd2 == NULL)
		return (pipes);
	if (pipes->cmd1->fd_out == -2 && pipes->cmd2->fd_in == 0)
	{
		pipes->fd = ft_calloc(2, sizeof(int *));
		if (!pipes->fd || pipe(pipes->fd) == -1)
		{
			ft_free_exec(pipes->cmd1);
			ft_free_exec(pipes->cmd2);
			ft_free_pipes(pipes);
			return (NULL);
		}
		pipes->cmd1->fd_out = pipes->fd[1];
		pipes->cmd2->fd_in = pipes->fd[0];
	}
	return (pipes);
}

t_exec	*ft_add_cmd(t_tokens *tkn, t_mini *mini, int in)
{
	t_exec	*ret;
	int		out;

	ret = NULL;
	in = check_in(mini, tkn, in);
	out = check_out(mini, tkn);
	while (tkn)
	{
		if (tkn->type == COMMAND)
		{
			ret = ft_init_exec(tkn, mini, in, out);
			if (ret == NULL)
				mini->status = 12;
			break ;
		}
		tkn = tkn->next;
	}
	return (ret);
}

t_exec	*ft_init_exec(t_tokens *token, t_mini *mini, int in, int out)
{
	t_tokens	*aux;
	char		*aux_cmd;
	t_exec		*exec;

	exec = ft_calloc(1, sizeof(t_exec));
	if (!exec)
		return (NULL);
	exec->fd_in = in;
	exec->fd_out = out;
	exec->path = ft_find_path(mini->env, token->value, mini->flag_path);
	aux = token;
	aux_cmd = ft_strdup("");
	while (aux && (aux->type == COMMAND || aux->type == ARGUMENT))
	{
		aux_cmd = ft_join_n(aux_cmd, aux->value, " ");
		aux = aux->next;
	}
	exec->cmd_mtx = ft_split(aux_cmd, ' ');
	free(aux_cmd);
	return (exec);
}
