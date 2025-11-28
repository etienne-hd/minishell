/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_in_scope.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 13:55:34 by ehode             #+#    #+#             */
/*   Updated: 2025/11/28 14:56:51 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	is_in_scope(char c)
{
	const char	scopes[] = {'\'', '"', 0};
	size_t		i;

	i = 0;
	while (scopes[i])
	{
		if (c == scopes[i])
			return (scopes[i]);
		i++;
	}
	return (0);
}
