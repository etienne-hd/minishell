/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_first_address.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:48:22 by ehode             #+#    #+#             */
/*   Updated: 2025/11/30 17:57:26 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"

void	*ft_find_first_address(size_t n, ...)
{
	va_list	args;
	size_t	i;
	void	*min;
	void	*current_addr;

	if (n == 0)
		return (0);
	va_start(args, n);
	i = 0;
	min = 0;
	while (i < n)
	{
		current_addr = va_arg(args, void *);
		if (current_addr != 0 && (min > current_addr || min == 0))
			min = current_addr;
		i++;
	}
	return (min);
}
