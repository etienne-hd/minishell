/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_token_chain_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:00:10 by ehode             #+#    #+#             */
/*   Updated: 2025/11/28 15:08:48 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

int	is_reserved_char(char c)
{
	if (c == '<' || c == '>' || c == '|' || ft_isspace(c))
		return (1);
	return (0);
}

size_t	get_text_length(char *text)
{
	char	scope;
	char	current_scope;
	size_t	i;

	current_scope = 0;
	i = 0;
	while (text[i])
	{
		scope = is_in_scope(text[i]);
		if (scope && current_scope == 0)
			current_scope = scope;
		else if (scope == current_scope)
			current_scope = 0;
		if (current_scope == 0 && is_reserved_char(text[i]))
			break ;
		i++;
	}
	return (i);
}
