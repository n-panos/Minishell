/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:50:28 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/10/20 13:18:28 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "eminishell.h"

// La logica de ordenacion cuando hay que añadir variables no la tengo clara

static char	*ft_orden(char **env, int env_len, char *str_exp, int *used);
static char	*ft_str_construct(int ref, char **env, char *str_exp, int i);

int	ft_export(t_mini *mini, char **cmd_mtx)
{
	char	*str_exp;
	int		*used;
	int		i;

	if (ft_strlen(cmd_mtx[0]) != 6)
		return (2);
	i = 1;
	while (cmd_mtx[i])
	{
		if (i > 1)
		{
			ft_export_more_args(mini, cmd_mtx[i]);
			return (0);
		}
		i++;
	}
	used = malloc(sizeof(int *));
	if (!used)
		return (-1);
	used[0] = '\0';
	str_exp = ft_strdup("");
	str_exp = ft_orden(env, 0, str_exp, used);
	printf("%s", str_exp);
	free(str_exp);
	return (0);
}

int	ft_export_more_args(t_mini *mini, char *cmd_mtx)
{
	char	*aux;
	int		i;

	i = ft_search_c(cmd_mtx, '=');
	if (i == -1)
		return (0);
	while (i >= 0)
	{
		if (ft_isalpha(cmd_mtx[i]) == 0)
		{
			printf("minishell: export: `%s': not a valid identifier", cmd_mtx)
			return (0);
		}
		i--;
	}
	aux = ft_add_to_env(mini->env, cmd_mtx);
	ft_mtx_free(mini->env);
	mini->env = ft_split(aux, '\n');
	free(aux);
	return (0);
}

char	*ft_add_to_env(char **env, char *add)
{
	char	*aux;

	return (aux);
}

static char	*ft_orden(char **env, int j, char *str_exp, int *used)
{
	int		ref;
	int		i;

	while (env[j])
	{
		i = 0;
		ref = 1;
		while (ft_check_list(used, ref) == 1)
			ref++;
		while (env[i])
		{
			if (ft_check_list(used, i) == 0)
			{
				if (ft_check_list(used, -1) == 1 && ref == 0)
					ref = i;
				else if (ft_strncmp(env[ref], env[i], ft_strlen(env[ref])) > 0)
					ref = i;
			}
			i++;
		}
		used = ft_add_used(used, ref);
		str_exp = ft_str_construct(ref, env, str_exp, i);
		j++;
	}
	return (str_exp);
}

static char	*ft_str_construct(int ref, char **env, char *str_exp, int i)
{
	char	*aux;
	char	**comillas;

	if (ft_strncmp(env[i], "_=/", 3) == 0)
		return (str_exp);
	comillas = ft_split(env[ref], '=');
	aux = ft_strfjoin(str_exp, "declare -x ");
	aux = ft_strfjoin(aux, comillas[0]);
	aux = ft_strfjoin(aux, "='");
	aux = ft_strfjoin(aux, comillas[1]);
	aux = ft_strfjoin(aux, "'\n");
	ft_mtx_free(comillas);
	return (aux);
}
