/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:21:20 by ehode             #+#    #+#             */
/*   Updated: 2025/11/01 16:58:27 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

// put
void	ft_putchar(int fd, char c, int *count);
void	ft_putstr(int fd, char *s, int *count);
void	ft_putaddr(int fd, size_t v, int prefix, int *count);
void	ft_putnbr(int fd, int nb, int *count);
void	ft_putunbr(int fd, unsigned int nb, int *count);
void	ft_putnbrhexa(int fd, unsigned int v, int in_lowercase, int *count);

// utils
int		printf_ft_startwith(const char *s, const char *val);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);

// printf / dprintf
int		ft_printf(const char *s, ...);
int		ft_dprintf(int fd, const char *s, ...);

#endif
