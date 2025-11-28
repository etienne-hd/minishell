/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:45:51 by ehode             #+#    #+#             */
/*   Updated: 2025/11/28 18:23:13 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"
#include "ctx.h"
#include "parsing.h"
#include <stdio.h>

const t_token_type	g_redirection_expected[] = {TEXT};
const t_token_type	g_text_expected[] = {TEXT, PIPE, REDIRECTION, END};
const t_token_type	g_pipe_expected[] = {TEXT};

static int	is_expected(const t_token_type *expected_type, size_t size,
	t_token_type type)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (expected_type[i] == type)
			return (1);
		i++;
	}
	return (0);
}

static int	check_expected_type(const t_token_type *expected_type, size_t size,
	t_list *token_lst)
{
	t_pre_token			*next_token;

	if (token_lst->next == NULL && is_expected(expected_type, size, END))
		return (0);
	else if (token_lst->next == NULL)
	{
		ft_dprintf(2, "minishell: syntax error near \
unexpected token 'newline'\n");
		return (1);
	}
	next_token = (t_pre_token *)token_lst->next->content;
	if (is_expected(expected_type, size, next_token->type))
		return (0);
	ft_dprintf(2, "minishell: syntax error near unexpected token '%s'\n",
		next_token->raw_content);
	return (1);
}

int	check_syntax(t_list *token_lst, t_ctx *ctx)
{
	t_pre_token	*token;
	int			error_occured;

	error_occured = 0;
	while (token_lst && error_occured == 0)
	{
		token = (t_pre_token *)token_lst->content;
		if (token->type == REDIRECTION)
			error_occured = check_expected_type(g_redirection_expected,
					sizeof(g_redirection_expected)
					/ sizeof(t_token_type), token_lst);
		else if (token->type == TEXT)
			error_occured = check_expected_type(g_text_expected,
					sizeof(g_text_expected)
					/ sizeof(t_token_type), token_lst);
		else
			error_occured = check_expected_type(g_pipe_expected,
					sizeof(g_pipe_expected)
					/ sizeof(t_token_type), token_lst);
		token_lst = token_lst->next;
	}
	if (error_occured)
		ctx->status_code = FAILURE;
	return (error_occured);
}
