/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:47:42 by ehode             #+#    #+#             */
/*   Updated: 2025/10/16 18:46:27 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_length;
	size_t	substr_length;
	char	*substr;

	if (!s)
		return (NULL);
	substr_length = 0;
	s_length = ft_strlen(s);
	while (start + substr_length < s_length && substr_length < len)
		substr_length++;
	i = 0;
	substr = ft_calloc(substr_length + 1, sizeof(char));
	if (!substr)
		return (NULL);
	while (i < substr_length)
	{
		substr[i] = s[start + i];
		i++;
	}
	return (substr);
}
