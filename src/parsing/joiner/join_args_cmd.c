/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_args_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 18:55:09 by ehode             #+#    #+#             */
/*   Updated: 2025/12/01 19:25:27 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

void	join_args_cmd(t_list *token_lst)
{
	t_token	*current_cmd;
	t_token	*current_token;
	t_list	*previous_token_lst;

	previous_token_lst = NULL;
	current_cmd = NULL;
	while (token_lst)
	{
		current_token = (t_token *)token_lst->content;
		if (current_token->type == CMD && current_cmd == NULL)
			current_cmd = current_token;
		else if (current_token->type == CMD && current_cmd != NULL)
		{
			ft_lstadd_back(&current_cmd->args, current_token->args);
			previous_token_lst->next = token_lst->next;
			free(current_token);
			free(token_lst);
			token_lst = previous_token_lst->next;
			continue ;
		}
		else if (current_token->type == PIPE)
			current_cmd = NULL;
		previous_token_lst = token_lst;
		token_lst = token_lst->next;
	}
}
