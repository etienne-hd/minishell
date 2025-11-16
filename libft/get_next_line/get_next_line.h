/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 16:04:57 by ehode             #+#    #+#             */
/*   Updated: 2025/11/01 16:56:52 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

char	*gnl_ft_strchr(char *s, char c);
size_t	gnl_ft_strlen(char *str);
void	gnl_ft_strcpy(char *dst, char *src);
char	*gnl_ft_strndup(char *str, size_t n);
char	*gnl_ft_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);

#endif