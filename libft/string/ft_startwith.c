/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_startwith.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 16:17:34 by ehode             #+#    #+#             */
/*   Updated: 2025/11/01 17:52:15 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_startwith(char *str, char *start)
{
	size_t	i;

	if (!str || !start)
		return (0);
	i = 0;
	while (str[i] == start[i] && str[i])
		i++;
	return (start[i] == '\0');
}
