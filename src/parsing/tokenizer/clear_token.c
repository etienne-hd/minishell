/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:15:37 by ehode             #+#    #+#             */
/*   Updated: 2025/11/28 17:39:14 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

void	clear_arg(void *ptr)
{
	t_arg	*arg;

	arg = (t_arg *)ptr;
	free(arg->raw_content);
	free(arg->arg);
	free(arg);
}

void	clear_token(void *ptr)
{
	t_token	*token;

	token = (t_token *)ptr;
	ft_lstclear(&token->args, clear_arg);
	free(token);
}