/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:42:36 by ehode             #+#    #+#             */
/*   Updated: 2025/12/03 00:28:25 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "parsing.h"

int	is_redirection(t_token *token)
{
	if (token->type == IN_FILE || token->type == IN_HERE_DOC
			|| token->type == OUT_FILE || token->type == OUT_FILE_APPEND)
		return (1);
	return (0);
}