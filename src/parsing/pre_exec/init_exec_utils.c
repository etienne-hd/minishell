/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:42:36 by ehode             #+#    #+#             */
/*   Updated: 2025/12/04 23:36:12 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "token.h"
#include "parsing.h"

void	init_redirection(t_file	*file, t_token *token)
{
	file->fd = -1;
	file->type = token->type;
	file->args = token->args;
}

int	is_redirection(t_token *token)
{
	if (token->type == IN_FILE || token->type == IN_HERE_DOC
		|| token->type == OUT_FILE || token->type == OUT_FILE_APPEND)
		return (1);
	return (0);
}
