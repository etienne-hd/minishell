/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:43:49 by ncorrear          #+#    #+#             */
/*   Updated: 2025/12/02 13:45:22 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "exec.h"
#include "libft.h"
#include "parsing.h"
#include <fcntl.h>
#include <string.h>

t_list	*get_cmd_list(t_list *token_list, t_ctx *ctx)
{
	t_list	*cmd_list;
	t_list	*current_cmd_list;
	t_token *current_token;
	t_process	*current_cmd;

	cmd_list = NULL;
	while (token_list)
	{
		current_token = (t_token *)token_list->content;
		if (current_token->type == CMD)
		{
			current_cmd = token_to_command(current_token, ctx);
			if (current_cmd)
			{
				current_cmd_list = ft_lstnew(current_cmd);
				if (current_cmd_list == NULL)
				{
					// TODO: Faire la gestion d'erreur
				}
				ft_lstadd_back(&cmd_list, current_cmd_list);
			}
		}
		token_list = token_list->next;
	}
	return (cmd_list);
}
