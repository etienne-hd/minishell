/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:45:51 by ehode             #+#    #+#             */
/*   Updated: 2025/12/01 18:45:09 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"
#include "ctx.h"
#include "parsing.h"
#include <stdio.h>

static int	check_redirection(t_pre_token *previous_token, t_list *token_lst)
{
	t_pre_token	*next_token;

	(void)previous_token;
	next_token = NULL;
	if (token_lst->next)
		next_token = (t_pre_token *)token_lst->next->content;
	if (next_token && next_token->type == TEXT)
		return (0);
	if (!next_token)
		ft_dprintf(2, "minishell: syntax error near \
unexpected token 'newline'\n");
	else
		ft_dprintf(2, "minishell: syntax error near unexpected token '%s'\n",
			next_token->raw_content);
	return (1);
}

static int	check_text(t_pre_token *previous_token, t_list *token_lst)
{
	t_pre_token	*next_token;

	(void)previous_token;
	next_token = NULL;
	if (token_lst->next)
		next_token = (t_pre_token *)token_lst->next->content;
	if (!next_token || next_token->type == TEXT
		|| next_token->type == REDIRECTION || next_token->type == PIPE)
		return (0);
	if (!next_token)
		ft_dprintf(2, "minishell: syntax error near \
unexpected token 'newline'\n");
	else
		ft_dprintf(2, "minishell: syntax error near unexpected token '%s'\n",
			next_token->raw_content);
	return (1);
}

static int	check_pipe(t_pre_token *previous_token, t_list *token_lst)
{
	t_pre_token	*next_token;

	next_token = NULL;
	if (token_lst->next)
		next_token = (t_pre_token *)token_lst->next->content;
	if (previous_token && next_token && (next_token->type == TEXT
			|| next_token->type == REDIRECTION))
		return (0);
	if (!previous_token)
		ft_dprintf(2, "minishell: syntax error near \
unexpected token '|'\n");
	else if (!next_token)
		ft_dprintf(2, "minishell: syntax error near \
unexpected token 'newline'\n");
	else
		ft_dprintf(2, "minishell: syntax error near unexpected token '%s'\n",
			next_token->raw_content);
	return (1);
}

int	check_syntax(t_list *token_lst, t_ctx *ctx)
{
	t_pre_token	*token;
	t_pre_token	*previous_token;
	int			error_occured;

	previous_token = NULL;
	error_occured = 0;
	while (token_lst && error_occured == 0)
	{
		token = (t_pre_token *)token_lst->content;
		if (token->type == REDIRECTION)
			error_occured = check_redirection(previous_token, token_lst);
		else if (token->type == TEXT)
			error_occured = check_text(previous_token, token_lst);
		else
			error_occured = check_pipe(previous_token, token_lst);
		previous_token = token;
		token_lst = token_lst->next;
	}
	if (error_occured)
		ctx->status_code = FAILURE;
	return (error_occured);
}
