/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:16:33 by ehode             #+#    #+#             */
/*   Updated: 2025/11/01 16:44:24 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr(int fd, char *s, int *count)
{
	int	s_length;
	int	length;

	if (!s)
	{
		ft_putstr(fd, "(null)", count);
		return ;
	}
	s_length = ft_strlen(s);
	length = write(fd, s, s_length);
	if (length > 0)
		*count += length;
}
