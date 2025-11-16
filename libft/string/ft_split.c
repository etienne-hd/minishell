/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:20:51 by ehode             #+#    #+#             */
/*   Updated: 2025/10/16 18:37:58 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ultimate_strlen(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static long	get_number_strs(char const *s, char c)
{
	size_t	i;
	size_t	length;
	long	number;

	i = 0;
	number = 0;
	while (s[i])
	{
		length = ultimate_strlen(s + i, c);
		if (length)
		{
			i += length;
			number += 1;
		}
		else
			i++;
	}
	return (number);
}

static int	allocate_strs(char **strs, char const *s, char c)
{
	size_t	i;
	size_t	length;
	size_t	number;

	i = 0;
	number = 0;
	while (s[i])
	{
		length = ultimate_strlen(s + i, c);
		if (length)
		{
			strs[number] = ft_calloc(length + 1, sizeof(char));
			if (!strs[number])
				return (1);
			ft_memcpy(strs[number], s + i, length);
			number += 1;
			i += length;
		}
		else
			i++;
	}
	return (0);
}

static void	free_strs(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

char	**ft_split(char const *s, char c)
{
	long	total_strs;
	char	**strs;

	if (!s)
		return (NULL);
	total_strs = get_number_strs(s, c);
	strs = ft_calloc(total_strs + 1, sizeof(char *));
	if (!strs)
		return (NULL);
	if (allocate_strs(strs, s, c))
	{
		free_strs(strs);
		return (NULL);
	}
	return (strs);
}
