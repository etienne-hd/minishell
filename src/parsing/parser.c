/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:35:50 by ehode             #+#    #+#             */
/*   Updated: 2025/12/02 12:58:02 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "ctx.h"
#include "error.h"
#include "ft_printf.h"
#include "libft.h"
#include "parsing.h"
#include "utils.h"
#include <stddef.h>

static void	print_token_lst(t_list *lst)
{
	t_token	*token;
	t_list	*current_args;
	char	*current_arg;

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
			current_arg = current_args->content;
			ft_printf("\t{raw_content: [%s]},\n", current_arg);
			current_args = current_args->next;
		}
		ft_printf("}\n");
		lst = lst->next;
	}
}

static void	print_cmd(t_cmd *cmd)
{
	size_t	i;

	ft_printf("CMD {\n");
	if (cmd != NULL)
	{
		ft_printf("\tpath = %s,\n", cmd->path);
		ft_printf("\tbuiltin = %i,\n", cmd->is_builtin);
		ft_printf("\tfd_in = %i,\n", cmd->fd_in);
		ft_printf("\tfd_out = %i,\n", cmd->fd_out);
		ft_printf("\targs = {\n");
		i = 0;
		while (cmd->args[i])
		{
			ft_printf("\t\t%s,\n", cmd->args[i]);
			i++;
		}
		ft_printf("\t}\n");
	}
	ft_printf("}\n");
}

int	parse(char *input, t_ctx *ctx)
{
	t_list	*pre_token_list;
	t_list	*token_list;

	// CHECK SCOPE
	if (is_valid_scope(input, ctx) == 0)
		return (1);
	// PRE TOKENIZE
	pre_token_list = get_pre_token_list(input);
	free(input);
	if (!pre_token_list)
		safe_exit(&ctx, "Malloc failed.");
	// CHECK SYNTAX
	if (check_syntax(pre_token_list, ctx))
	{
		ft_lstclear(&pre_token_list, clear_pre_token);
		return (1);
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
	(void) print_token_lst;
	// print_token_lst(token_list);
	t_cmd *test = token_to_command(token_list->content, ctx);
	print_cmd(test);
	// TODO : une focntion clear_token qui clear pas les char * dedans -> puique meme ptr dans cmd
	ft_lstclear(&token_list, clear_token);
	ctx->status_code = SUCCESS;
	return (0);
}
