/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrhexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:26:31 by ehode             #+#    #+#             */
/*   Updated: 2025/11/01 16:44:12 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbrhexa(int fd, unsigned int v, int in_lowercase, int *count)
{
	const char	hexa_lowercase[] = "0123456789abcdef";
	const char	hexa_uppercase[] = "0123456789ABCDEF";

	if (v > 15)
		ft_putnbrhexa(fd, v / 16, in_lowercase, count);
	if (in_lowercase)
		ft_putchar(fd, ((char *)hexa_lowercase)[v % 16], count);
	else
		ft_putchar(fd, ((char *)hexa_uppercase)[v % 16], count);
}
