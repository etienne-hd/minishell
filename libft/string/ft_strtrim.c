/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:08:57 by ehode             #+#    #+#             */
/*   Updated: 2025/10/16 18:35:27 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	s1_length;
	char	*strtrim;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && is_in_set(*s1, set))
		s1++;
	s1_length = ft_strlen((char *)s1);
	i = 0;
	while (s1_length && is_in_set(*(s1 + s1_length - i - 1), set))
		i++;
	strtrim = ft_calloc(s1_length - i + 1, sizeof(char));
	if (!strtrim)
		return (NULL);
	ft_memcpy(strtrim, s1, s1_length - i);
	return (strtrim);
}
