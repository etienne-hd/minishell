/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 11:53:11 by ehode             #+#    #+#             */
/*   Updated: 2025/10/15 18:00:54 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	s_length;
	char	*new_s;

	s_length = ft_strlen(s);
	new_s = ft_calloc(s_length + 1, sizeof(char));
	if (!new_s)
		return (NULL);
	i = 0;
	while (i < s_length)
	{
		new_s[i] = s[i];
		i++;
	}
	return (new_s);
}
