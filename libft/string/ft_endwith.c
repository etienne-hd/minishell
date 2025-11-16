/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_endwith.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 16:17:34 by ehode             #+#    #+#             */
/*   Updated: 2025/11/01 17:52:38 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_endwith(char *str, char *end)
{
	size_t	i;
	size_t	end_length;
	size_t	str_length;

	if (!str || !end)
		return (0);
	i = 0;
	end_length = ft_strlen(end);
	str_length = ft_strlen(str);
	while (str[str_length - i - 1] == end[end_length - i - 1]
		&& i < end_length && i < str_length)
		i++;
	return (end[i] == '\0');
}
