/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:48:04 by ehode             #+#    #+#             */
/*   Updated: 2025/12/01 18:44:11 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

int	handle_tilde(char **s)
{
	char	*tmp;

	if ((*s)[0] == '~' && ((*s)[1] == 0 || (*s)[1] == '/'))
	{
		tmp = *s;
		*s = ft_strjoin("$HOME", *s + 1);
		free(tmp);
		if (!*s)
			return (1);
	}
	return (0);
}
