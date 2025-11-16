/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:36:19 by ehode             #+#    #+#             */
/*   Updated: 2025/10/16 17:04:01 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	size_t	j;

	if (!dest && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		if (src > dest)
			((char *)dest)[i] = ((char *)src)[i];
		else
		{
			j = n - i - 1;
			((char *)dest)[j] = ((char *)src)[j];
		}
		i++;
	}
	return (dest);
}
