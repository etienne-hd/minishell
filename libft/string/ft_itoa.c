/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:03:02 by ehode             #+#    #+#             */
/*   Updated: 2025/10/16 19:42:21 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	total_length(int n)
{
	size_t	length;

	if (n == 0)
		return (1);
	length = 0;
	if (n < 0)
		length++;
	while (n != 0)
	{
		n /= 10;
		length++;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	size_t	length;
	size_t	i;
	char	*nbr;

	length = total_length(n);
	nbr = ft_calloc(length + 1, sizeof(char));
	if (!nbr)
		return (NULL);
	if (n == 0)
		nbr[0] = '0';
	else
	{
		i = 0;
		if (n < 0)
			nbr[0] = '-';
		while (n != 0)
		{
			if (n < 0)
				nbr[length - i++ - 1] = ((n % 10 * -1) + '0');
			else
				nbr[length - i++ - 1] = (n % 10 + '0');
			n /= 10;
		}
	}
	return (nbr);
}
