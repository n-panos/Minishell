#include "eminishell.h"

typedef enum s_type
{
	COMMAND,
	ARGUMENT,
	PIPE,
	REDIRECT_INPUT,
	REDIRECT_OUTPUT,
	REDIRECT_APPEND,
	HEREDOC,
	DELIMITER
}	t_type;

typedef struct s_mini
{
	t_tokens	*tk_lst;
}	t_mini;

typedef struct s_exec
{
	char	*path;
	char	**cmd_mtx;
	int		fd_in;
	int		fd_out;
}				t_exec;

typedef	struct	s_pipe
{
	t_exec	**cmd;
	int		**fd;
}				t_pipe;

typedef struct s_tokens
{
	char				*value;
	t_type				type;
	char				*tool;
	struct s_tokens		*next;
	struct s_tokens		*prev;
}	t_tokens;


int	ft_preprocess_pipe(t_token *token, int pipe_num, char **env)
{
	t_pipe	*pipe;
    t_token	*aux_token;
	int		i;

	aux_token = token;
	pipe = ft_pipe_init(pipe_num);
	i = 0;
	while (aux_token)
	{
		if (aux_token->type == COMMAND)
			{
				pipe->cmd[i] = ft_init_exec(aux_token, env);
				ft_in_out_pipe(pipe->cmd[i], aux_token);
				i++;
			}
		aux_token = aux_token->next;
	}
	return (ft_exec_pipe(pipe));
}

void	ft_in_out_pipe(t_exec *exec, t_token *token)
{
	t_token	*aux_token;

	aux_token = token->next;
	while (aux_token)
	{
		if (aux_token->type == PIPE || aux_token->type == COMMAND)
			break ;
		ft_in_out_type(aux_token, exec);
		aux_token = aux_token->next;
	}
}

int	ft_exec_pipe(t_pipe *pipe, char **env, int pipe_num)
{
	pid_t	*pidc;
	int		i;
	pid_t	*pidc;

	i = 0;
	while (i <= pipe_num)
	{
		pidc = -1;
		ret = ft_builtin_check(exec);
		if (ret == -1)
			ft_error_cmd(pipe->cmd[i]->cmd_mtx[0]);
		else if (ret == 2)
		{
			if (pipe->cmd[i]->path == NULL)
				ft_error_cmd(pipe->cmd[i]->cmd_mtx[0]);
			else
				pidc = ft_exec_solo(env, pipe->cmd[i]);
		}
		if (pidc > -1)
			waitpid(pidc, NULL, 0);
		i++;
	}
	return (0);
}

void	ft_error_cmd(char *str)
{
	ft_putstr_fd("zsh: command not found: ", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("\n", 1);
}

t_pipe	*ft_pipe_init(int pipe_num)
{
	t_pipe	*pipe;
	int		i;

	i = 0;
	pipe = ft_calloc(1, sizeof(t_pipe));
	if(!pipe)
		return (NULL);
	while (i <= pipe_num)
	{
		pipe->cmd[i] = ft_calloc(1, sizeof(t_exec *));
		i++;
	}
	if (!pipe->cmd1 || !pipe->cmd2)
		return (NULL);
	i = 0;
	while (i < pipe_num)
	{
		pipe->fd[i] = ft_calloc(2, sizeof(int));
		if (pipe(pipe->fd[i]) == -1)
			exit(EXIT_FAILURE);
		i++;
	}
	ft_in_out_default(pipe, pipe_num);
	return (pipe);
}

void	ft_in_out_default(t_pipe *pipe, int pipe_num)
{
	int	i;

	pipe->cmd[0]->fd_in = 0;
	pipe->cmd[0]->fd_out = pipe->fd[0][1];
	i = 1;
	while (i < (pipe_num - 1))
	{
		pipe->cmd[i]->fd_in = pipe->fd[i - 1][0];
		pipe->cmd[i]->fd_out = pipe->fd[i][1];
		i++;
	}
	pipe->cmd[pipe_num]->fd_in = pipe->fd[i - 1][0];
	pipe->cmd[pipe_num]->fd_out = 1;
}
