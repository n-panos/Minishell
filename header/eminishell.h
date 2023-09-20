/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eminishell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:37:22 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/09/20 12:52:32 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EMINISHELL_H
# define EMINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>

//      HAND CRAFTED FUNCTIONS -- BUILTINS

int		ft_exec_pwd(void);
int		ft_exec_echo(char *str, int flag);
int		ft_exec_env(char **env);
int		ft_exec_export(char **env);

#endif