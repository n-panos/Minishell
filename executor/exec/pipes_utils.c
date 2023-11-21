#include "../header/eminishell.h"

t_tokens	*ft_return_pipe(t_tokens *tkn)
{
	while (tkn)
	{
		if (tkn->type == PIPE)
		{
			if (tkn->next)
				tkn = tkn->next;
			break ;
		}
		tkn = tkn->next;
	}
	return (tkn);
}

int	ft_is_exit(t_mini *mini, t_tokens *lst)
{
	t_tokens	*tkn;

	tkn = lst;
	while (tkn)
	{
		if (tkn->type == PIPE)
			break ;
		if (tkn->type == COMMAND && ft_strncmp(tkn->value, "exit", 4) == 0 && \
		ft_strlen(tkn->value) == 4)
			return (mini->status = 1, 1);
		if (tkn->type == COMMAND && ft_strncmp(tkn->value, "bash", 4) == 0 && \
		ft_strlen(tkn->value) == 4)
			return (mini->status = 1, 1);
		if (tkn->type == COMMAND && ft_strncmp(tkn->value, "./minishell", 11) \
		== 0 && ft_strlen(tkn->value) == 11)
			return (mini->status = 1, 1);
		if (tkn->type == COMMAND && ft_strncmp(tkn->value, "export", 6) \
		== 0 && ft_strlen(tkn->value) == 6)
			return (mini->status = 1, 1);
		tkn = tkn->next;
	}
	return (0);
}
