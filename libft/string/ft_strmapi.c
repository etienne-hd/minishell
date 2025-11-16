/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:47:47 by ehode             #+#    #+#             */
/*   Updated: 2025/10/16 18:26:50 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ns;
	size_t	i;

	if (!s || !f)
		return (NULL);
	ns = ft_strdup(s);
	if (!ns)
		return (NULL);
	i = 0;
	while (ns[i])
	{
		ns[i] = f(i, s[i]);
		i++;
	}
	return (ns);
}
