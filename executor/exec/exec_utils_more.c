
#include "../header/eminishell.h"

void	ft_waiting(int n)
{
	int	status;

	while (n > 0)
	{
		wait(&status);
		n--;
	}
}

int	ft_check_out(t_mini *mini, t_tokens *tkn)
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
			ret = open(atkn->next->value, \
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (atkn->type == REDIRECT_APPEND)
			ret = open(atkn->next->value, \
			O_WRONLY | O_APPEND, 0644);
		if (ret == -1)
			return (ft_error_cmd(mini, atkn->next->value, 0, -1));
		atkn = atkn->next;
	}
	return (ret);
}

int	ft_check_in(t_mini *mini, t_tokens *tkn, int in)
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
		if (atkn->type == REDIRECT_INPUT)
			ret = open(atkn->next->value, O_RDONLY);
		else if (atkn->type == HEREDOC)
			ret = here_doc(atkn->next->value);
		if (ret == -1)
			return (ft_error_cmd(mini, atkn->next->value, -1 , 0));
		atkn = atkn->next;
	}
	return (ret);
}
