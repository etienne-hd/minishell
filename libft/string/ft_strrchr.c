/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:19:01 by ehode             #+#    #+#             */
/*   Updated: 2025/10/15 18:38:07 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	s_length;
	size_t	i;

	s_length = ft_strlen(s);
	if ((unsigned char)c == 0)
		return ((char *)s + s_length);
	i = 0;
	while (s[i])
	{
		if ((unsigned char)s[s_length - i - 1] == (unsigned char)c)
			return ((char *)s + s_length - i - 1);
		i++;
	}
	return (NULL);
}
