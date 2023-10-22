/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipanos-o <ipanos-o@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 09:57:32 by ipanos-o          #+#    #+#             */
/*   Updated: 2023/05/31 09:59:24 by ipanos-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 1

# include <stddef.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

char		*get_next_line(int fd);

//		Libft modificados

size_t		gnl_strlen(const char *s);
int			gnl_strchr(char *s, char c);
char		*gnl_strjoin(char *s1, char *s2);
void		*gnl_calloc(size_t count, size_t size);

#endif