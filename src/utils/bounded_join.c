/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounded_join.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:38:57 by ehode             #+#    #+#             */
/*   Updated: 2025/11/30 17:39:35 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"

int	bounded_join(char **origin, size_t n, char *value, char *end)
{
	char	*temp;
	char	*begin;

	begin = ft_strndup(*origin, n);
	if (!begin)
	{
		free(value);
		return (1);
	}
	temp = ft_strnjoin(3, begin, value, end);
	if (!temp)
	{
		free(value);
		free(begin);
		return (1);
	}
	free(begin);
	free(*origin);
	free(value);
	*origin = temp;
	return (0);
}
