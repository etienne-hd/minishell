/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_scope.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:45:51 by ehode             #+#    #+#             */
/*   Updated: 2025/11/28 15:24:25 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "ft_printf.h"
#include "ctx.h"
#include "utils.h"

/**
 * @brief Return if all scope are correctly close in the string
 *
 * @param s 
 * @param ctx 
 * @return boolean
 */
int	is_valid_scope(char *s, t_ctx *ctx)
{
	char		scope;
	char		current_scopes;
	size_t		i;

	current_scopes = 0;
	i = 0;
	while (s[i])
	{
		scope = is_in_scope(s[i]);
		if (scope && current_scopes == 0)
			current_scopes = scope;
		else if (current_scopes == scope)
			current_scopes = 0;
		i++;
	}
	if (current_scopes == 0)
		return (1);
	ft_dprintf(2, "minishell: syntax error unclosed scope near '%c'\n",
		current_scopes);
	ctx->status_code = CMD_BAD_USAGE;
	return (0);
}
