/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_env_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ediaz--c <ediaz--c@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:46:09 by ediaz--c          #+#    #+#             */
/*   Updated: 2023/12/15 15:52:03 by ediaz--c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../executor/header/eminishell.h"

char	*fisrt_arg(char *str, char **cmd)
{
	size_t	len;
	int		i;

	i = -1;
	len = ft_strlen(str) + 3;
	*cmd = malloc(sizeof(char) * len);
	if (*cmd == NULL)
		return (NULL);
	(*cmd)[0] = '"';
	while (str[++i])
		(*cmd)[i + 1] = str[i];
	(*cmd)[i + 1] = '"';
	(*cmd)[i + 2] = '\0';
	return (*cmd);
}

char	*other_arg(char **split, char **other)
{
	size_t	len;
	int		i;

	len = 1;
	i = 1;
	while (split[i])
		len += ft_strlen(split[i++]) + 1;
	*other = malloc(sizeof(char) * len);
	if (*other == NULL)
		return (NULL);
	i = 1;
	ft_strlcpy(*other, " ", len);
	ft_strlcat(*other, split[i++], len);
	while (split[i])
	{
		printf("%s\n", split[i]);
		ft_strlcat(*other, " ", len);
		ft_strlcat(*other, split[i++], len);
	}
	return (*other);
}

char	*ft_expand_multi(char **split)
{
	char	*cmd;
	char	*other;

	if (fisrt_arg(split[0], &cmd) == NULL)
		return (NULL);
	if (other_arg(split, &other) == NULL)
		return (NULL);
	cmd = ft_strfjoin(cmd, other);
	free(other);
	if (cmd == NULL)
		return (NULL);
	return (cmd);
}
