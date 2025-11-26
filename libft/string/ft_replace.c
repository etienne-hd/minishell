/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:17:02 by ehode             #+#    #+#             */
/*   Updated: 2025/11/20 16:25:53 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <stdio.h>

static char	*ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
	char	*new_s;
	size_t	sx_length[3];

	sx_length[0] = ft_strlen(s1);
	sx_length[1] = ft_strlen(s2);
	sx_length[2] = ft_strlen(s3);
	new_s = malloc((sx_length[0] + sx_length[1] + sx_length[2] + 1)
			* sizeof(char));
	if (!new_s)
		return (NULL);
	ft_memcpy(new_s, s1, sx_length[0]);
	ft_memcpy(new_s + sx_length[0], s2, sx_length[1]);
	ft_memcpy(new_s + sx_length[0] + sx_length[1], s3, sx_length[2]);
	new_s[sx_length[0] + sx_length[1] + sx_length[2]] = 0;
	return (new_s);
}

static char	*process(char *s, const char *target, const char *new, size_t i)
{
	size_t	target_len;
	char	*begin;
	char	*end;
	char	*new_s;

	target_len = ft_strlen(target);
	begin = ft_strndup(s, i);
	if (!begin)
	{
		free(s);
		return (NULL);
	}
	end = ft_strdup(s + i + target_len);
	free(s);
	if (!end)
	{
		free(begin);
		return (NULL);
	}
	new_s = ft_strjoin3(begin, new, end);
	free(end);
	free(begin);
	return (new_s);
}

char	*ft_replace(const char *s, const char *target, const char *new)
{
	size_t	target_len;
	size_t	i;
	char	*new_s;

	new_s = ft_strdup(s);
	if (!s || !target || !new)
		return (new_s);
	target_len = ft_strlen(target);
	if (target_len == 0)
		return (new_s);
	i = 0;
	while (new_s[i])
	{
		if (ft_strncmp(new_s + i, target, target_len) == 0)
		{
			new_s = process(new_s, target, new, i);
			if (!new_s)
				return (NULL);
			i += ft_strlen(new);
		}
		else
			i++;
	}
	return (new_s);
}
