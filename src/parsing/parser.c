/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:35:50 by ehode             #+#    #+#             */
/*   Updated: 2025/12/05 01:06:59 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "error.h"
#include "exec.h"
#include "libft.h"
#include "parsing.h"
#include "utils.h"
#include <stddef.h>

t_exec	*parse(char *input, t_ctx *ctx)
{
	t_list	*pre_token_list;
	t_list	*token_list;
	t_exec	*exec;

	set_signal_status_code(ctx);
	// CHECK SCOPE
	if (is_valid_scope(input, ctx) == 0)
	{
		free(input);
		return (NULL);
	}
	// PRE TOKENIZE
	pre_token_list = get_pre_token_list(input);
	free(input);
	if (!pre_token_list)
		safe_exit(&ctx, "Malloc failed.");
	// CHECK SYNTAX
	if (check_syntax(pre_token_list, ctx))
	{
		ft_lstclear(&pre_token_list, clear_pre_token);
		return (NULL);
	}
	// TOKENIZE
	token_list = get_token_list(pre_token_list);
	ft_lstclear(&pre_token_list, clear_pre_token);
	// JOIN ARGS
	join_args_cmd(token_list);
	if (!token_list)
		safe_exit(&ctx, "Malloc failed.");
	// EXPAND
	if (expand_tokens(token_list, ctx))
	{
		ft_lstclear(&token_list, clear_token);
		safe_exit(&ctx, "Malloc failed.");
	}
	// (void) print_token_lst;
	exec = init_exec(token_list, ctx);
	if (exec == NULL)
	{
		ft_lstclear(&token_list, clear_token);
		safe_exit(&ctx, "Malloc failed.");
	}
	ft_lstclear(&token_list, clear_token_keep_cmd_arg);
	return (exec);
}
