/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_startwith.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:09:57 by ehode             #+#    #+#             */
/*   Updated: 2025/11/01 16:58:14 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printf_ft_startwith(const char *s, const char *val)
{
	size_t	i;

	i = 0;
	while (s[i] == val[i] && val[i] && s[i])
		i++;
	if (val[i] == '\0')
		return (1);
	return (0);
}
