/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nacho <nacho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:50:28 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/11/11 13:46:30 by nacho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/eminishell.h"

// La logica de ordenacion cuando hay que añadir variables no la tengo clara

static char	*ft_orden(char **env, int env_len, char *str_exp, int *used);
static char	*ft_str_construct(int ref, char **env, char *str_exp);
int			ft_export_more_args(t_mini *mini, char *cmd_mtx);

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
		//ft_funcion de quitar tabs y espacios(preguntar a EricK)
		if (i >= 1)
			ft_export_more_args(mini, cmd_mtx[i]);
		i++;
	}
	if (i > 1)
		return (0);
	used = malloc(sizeof(int *));
	if (!used)
		return (-1);
	used[0] = '\0';
	str_exp = ft_strdup("");
	str_exp = ft_orden(mini->env, 0, str_exp, used);
	printf("%s", str_exp);
	free(str_exp);
	return (0);
}

int	ft_export_more_args(t_mini *mini, char *arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		if (i > 0 && arg[i] == '=')
			break ;
		if (arg[i] != '_' && (ft_isalnum(arg[i]) == 0 || \
		(i == 0 && ft_isalpha(arg[i]) == 0)))
		{
			printf("minishell: export: `%s': not a valid identifier\n", arg);
			return (0);
		}
		i++;
	}
	ft_change_env_var(mini, arg);
	return (0);
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
			ref = ft_check_ref(used, i, ref, env);
			i++;
		}
		used = ft_add_used(used, ref);
		str_exp = ft_str_construct(ref, env, str_exp);
		j++;
	}
	free(used);
	return (str_exp);
}

static char	*ft_str_construct(int ref, char **env, char *str_exp)
{
	char	*aux;
	char	**comillas;

	if (ft_strncmp(env[ref], "_=/", 3) == 0)
		return (str_exp);
	comillas = ft_split(env[ref], '=');
	aux = ft_strfjoin(str_exp, "declare -x ");
	aux = ft_strfjoin(aux, comillas[0]);
	if (comillas[1])
	{
		aux = ft_strfjoin(aux, "='");
		aux = ft_join_n(aux, comillas[1], "'\n");
	}
	else
		aux = ft_strfjoin(aux, "\n");
	ft_mtx_free(comillas);
	return (aux);
}
