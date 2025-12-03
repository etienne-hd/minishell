/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:15:37 by ehode             #+#    #+#             */
/*   Updated: 2025/12/03 02:09:02 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

void	clear_token_keep_cmd_arg(void *ptr)
{
	t_token	*token;

	if (!ptr)
		return ;
	token = (t_token *)ptr;
	if (token->type == CMD)
		ft_lstclear(&token->args, NULL);
	free(token);
}

void	clear_token(void *ptr)
{
	t_token	*token;

	if (!ptr)
		return ;
	token = (t_token *)ptr;
	ft_lstclear(&token->args, free);
	free(token);
}
