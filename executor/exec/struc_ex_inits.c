#include "../header/eminishell.h"

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
