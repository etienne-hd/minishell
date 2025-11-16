/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:51:34 by ehode             #+#    #+#             */
/*   Updated: 2025/11/01 16:43:40 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(int fd, int nb, int *count)
{
	if (nb == -2147483648)
	{
		ft_putstr(fd, "-2147483648", count);
		return ;
	}
	if (nb < 0)
	{
		ft_putchar(fd, '-', count);
		nb *= -1;
	}
	if (nb > 9)
		ft_putnbr(fd, nb / 10, count);
	ft_putchar(fd, nb % 10 + '0', count);
}
