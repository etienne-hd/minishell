/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:35:50 by ehode             #+#    #+#             */
/*   Updated: 2025/11/28 18:48:05 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "error.h"
#include "libft.h"
#include "parsing.h"
#include "utils.h"

static void	print_pre_token_lst(t_list *lst)
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

static void	print_token_lst(t_list *lst)
{
	t_token	*token;
	t_list	*current_args;
	t_arg	*current_arg;

	while (lst)
	{
		token = (t_token *)lst->content;
		if (token->type == CMD)
			ft_printf("CMD: {\n");
		else if (token->type == PIPE)
			ft_printf("PIPE: {\n");
		else if (token->type == IN_FILE)
			ft_printf("REDIRECTION: {\n\tIN_FILE,\n");
		else if (token->type == IN_HERE_DOC)
			ft_printf("REDIRECTION: {\n\tIN_HERE_DOC,\n");
		else if (token->type == OUT_FILE)
			ft_printf("REDIRECTION: {\n\tOUT_FILE,\n");
		else
			ft_printf("REDIRECTION: {\n\tOUT_FILE_APPEND,\n");
		current_args = token->args;
		while (current_args)
		{
			current_arg = (t_arg *)current_args->content;
			ft_printf("\t{raw_content: %s, is_expanded: %d},\n",
				current_arg->raw_content, current_arg->is_expanded);
			current_args = current_args->next;
		}
		ft_printf("}\n");
		lst = lst->next;
	}
}

int	parse(char *input, t_ctx *ctx)
{
	t_list	*pre_token_list;
	t_list	*token_list;

	ctx->status_code = SUCCESS;
	if (is_valid_scope(input, ctx) == 0)
		return (1);
	pre_token_list = get_pre_token_list(input);
	if (!pre_token_list)
	{
		free(input);
		safe_exit(&ctx, "Malloc failed.");
	}
	if (check_syntax(pre_token_list, ctx))
	{
		ft_lstclear(&pre_token_list, clear_pre_token);
		return (1);
	}
	token_list = get_token_list(pre_token_list);
	if (!token_list)
	{
		free(input);
		safe_exit(&ctx, "Malloc failed.");
		ft_lstclear(&pre_token_list, clear_pre_token);
		return (1);
	}
	(void)print_pre_token_lst;
	print_token_lst(token_list);
	ft_lstclear(&pre_token_list, clear_pre_token);
	ft_lstclear(&token_list, clear_token);
	return (0);
}
