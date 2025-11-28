/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:35:50 by ehode             #+#    #+#             */
/*   Updated: 2025/11/28 16:11:22 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "error.h"
#include "parsing.h"
#include "utils.h"

static void	print_token_lst(t_list *lst)
{
	t_pre_token	*token;

	while (lst)
	{
		token = (t_pre_token *)lst->content;
		if (token->type == REDIRECTION)
			ft_printf("REDIRECTION: {content: %s}\n", token->raw_content);
		if (token->type == PIPE)
			ft_printf("PIPE: {content: %s}\n", token->raw_content);
		if (token->type == TEXT)
			ft_printf("TEXT: {content: %s}\n", token->raw_content);
		lst = lst->next;
	}
}

int	parse(char *input, t_ctx *ctx)
{
	t_list	*pre_token;

	ctx->status_code = SUCCESS;
	if (is_valid_scope(input, ctx) == 0)
		return (1);
	pre_token = get_pre_token_list(input);
	if (!pre_token)
	{
		free(input);
		safe_exit(&ctx, "Malloc failed");
	}
	if (!check_syntax(pre_token, ctx))
	{
		print_token_lst(pre_token);
		ft_lstclear(&pre_token, clear_pre_token);
		return (0);
	}
	ft_lstclear(&pre_token, clear_pre_token);
	return (1);
}
