/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:35:50 by ehode             #+#    #+#             */
/*   Updated: 2025/12/02 18:30:15 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "error.h"
#include "exec.h"
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

static void	print_cmd(t_process *cmd)
{
	size_t	i;

	ft_printf("CMD {\n");
	if (cmd != NULL)
	{
		ft_printf("\tpath = %s,\n", cmd->path);
		ft_printf("\tbuiltin = %i,\n", cmd->is_builtin);
		ft_printf("\tfile_in = %p,\n", cmd->file_in);
		ft_printf("\tfile_out = %p,\n", cmd->file_out);
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

static void	print_file(t_file *file)
{
	if (file)
	{
		ft_printf("FILE {\n");
		ft_printf("\taddress = %p,\n", file);
		if (file->type == PIPE)
			ft_printf("PIPE: {\n");
		else if (file->type == IN_FILE)
			ft_printf("\ttype: IN_FILE,\n");
		else if (file->type == IN_HERE_DOC)
			ft_printf("\ttype: IN_HERE_DOC,\n");
		else if (file->type == OUT_FILE)
			ft_printf("\ttype: OUT_FILE,\n");
		else
			ft_printf("\ttype: OUT_FILE_APPEND,\n");
		if (file->args)
			ft_printf("\t%s\n", file->args->content);
		ft_printf("}\n");
	}
}

static void	print_cmd_list(t_exec *cmd_list)
{
	t_list	*processes;
	t_list	*files;

	processes = cmd_list->processes;
	files = cmd_list->files;
	ft_printf("\n================\nfiles_list\n====================\n");
	while (files)
	{
		print_file(files->content);
		files = files->next;
	}
	ft_printf("\n================\nprocess_list\n====================\n");
	while (processes)
	{
		print_cmd(processes->content);
		processes = processes->next;
	}
}

int	parse(char *input, t_ctx *ctx)
{
	t_list	*pre_token_list;
	t_list	*token_list;
	t_exec	*exec;

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
	// (void) print_token_lst;
	print_token_lst(token_list);
	exec = init_exec(token_list, ctx);
	print_cmd_list(exec);
	ctx->status_code = SUCCESS;
	ft_lstclear(&exec->files, free);
	ft_lstclear(&exec->processes, clear_process_keep_args);
	free(exec);
	ft_lstclear(&token_list, clear_token);
	return (0);
}
