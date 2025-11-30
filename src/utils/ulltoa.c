/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ulltoa.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:52:46 by ncorrear          #+#    #+#             */
/*   Updated: 2025/11/30 11:35:24 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"

char	*ft_ulltoa(unsigned long long nbr)
{
	static char	buffer[22];
	char		*cursor;

	ft_bzero(buffer, sizeof(buffer));
	cursor = &buffer[20];
	while (nbr / 10 != 0)
	{
		*cursor-- = nbr % 10 + '0';
		nbr /= 10;
	}
	*cursor = nbr % 10 + '0';
	return (cursor);
}
