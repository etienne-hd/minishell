/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 15:10:09 by ehode             #+#    #+#             */
/*   Updated: 2025/12/01 22:43:34 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "libft.h"
#include "parsing.h"

int	expand_tokens(t_list *tokens, t_ctx *ctx)
{
	t_token	*current_token;

	while (tokens)
	{
		current_token = (t_token *)tokens->content;
		if (expand(current_token, ctx))
			return (1);
		tokens = tokens->next;
	}
	return (0);
}
