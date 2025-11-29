/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:07:07 by ehode             #+#    #+#             */
/*   Updated: 2025/11/29 18:27:17 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>
#include <stddef.h>

static size_t	get_total_length(size_t n, va_list args)
{
	va_list	args_copy;
	size_t	total_length;
	size_t	i;

	va_copy(args_copy, args);
	total_length = 0;
	i = 0;
	while (i++ < n)
		total_length += ft_strlen((char *)va_arg(args_copy, char *));
	va_end(args_copy);
	return (total_length);
}

static void	join_str(size_t n, char *dest, va_list *args)
{
	char	*current_str;
	size_t	i;
	size_t	j;
	size_t	k;	

	i = 0;
	k = 0;
	while (i < n)
	{
		current_str = (char *)va_arg(*args, char *);
		j = 0;
		while (current_str[j])
		{
			dest[k] = current_str[j];
			j++;
			k++;
		}
		i++;
	}
	dest[k] = 0;
}

char	*ft_strnjoin(size_t n, ...)
{
	va_list	args;
	size_t	total_length;
	char	*result;

	va_start(args, n);
	total_length = get_total_length(n, args);
	va_start(args, n);
	result = malloc((total_length + 1) * sizeof(char));
	if (!result)
	{
		va_end(args);
		return (NULL);
	}
	join_str(n, result, &args);
	va_end(args);
	return (result);
}
