/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:18:40 by ehode             #+#    #+#             */
/*   Updated: 2025/10/16 13:52:59 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	big_length;

	i = 0;
	if (!len && little[0] == '\0')
		return ((char *)big);
	if (!len)
		return (NULL);
	big_length = ft_strlen(big);
	while (i <= big_length && i < len)
	{
		j = 0;
		while (i + j < len && big[i + j] == little[j] && i + j <= big_length
			&& little[j])
			j++;
		if (little[j] == '\0')
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
