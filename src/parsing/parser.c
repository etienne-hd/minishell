/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:35:50 by ehode             #+#    #+#             */
/*   Updated: 2025/11/27 15:38:17 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "error.h"
#include "parsing.h"

int	parse(char *input, t_ctx *ctx)
{
	ctx->status_code = SUCCESS;
	if (!is_valid_scope(input, ctx))
		return (1);
	return (0);
}