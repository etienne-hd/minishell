/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_chain.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 16:49:57 by ehode             #+#    #+#             */
/*   Updated: 2025/11/28 18:47:46 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include <stdio.h>

static t_list	*get_args(t_list *pre_token_list, int n)
{
	t_list		*arg_node;
	t_list		*args_list;
	t_arg		*arg;
	t_pre_token	*pre_token;
	int			i;

	args_list = NULL;
	i = 0;
	while (pre_token_list && (n == -1 || i++ < n))
	{
		pre_token = (t_pre_token *)pre_token_list->content;
		if (pre_token->type != TEXT)
			break;
		arg = ft_calloc(1, sizeof(t_arg));
		if (!arg)
		{
			ft_lstclear(&args_list, clear_arg);
			return (NULL);
		}
		arg->raw_content = ft_strdup(pre_token->raw_content); 
		arg_node = ft_lstnew(arg);
		if (arg->raw_content == NULL || arg_node == NULL)
		{
			free(arg->raw_content);
			free(arg_node);
			free(arg);
			ft_lstclear(&args_list, clear_arg);
			return (NULL);
		}
		ft_lstadd_back(&args_list, arg_node);
		pre_token_list = pre_token_list->next;
	}
	return (args_list);
}

static t_token	*get_redirection_token(t_list **pre_token_list)
{
	t_token		*token;
	t_pre_token	*pre_token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	pre_token = (t_pre_token *)(*pre_token_list)->content;
	if (ft_strncmp(pre_token->raw_content, "<<", 2) == 0)
		token->type = IN_HERE_DOC;
	else if (ft_strncmp(pre_token->raw_content, "<", 1) == 0)
		token->type = IN_FILE;
	else if (ft_strncmp(pre_token->raw_content, ">>", 2) == 0)
		token->type = OUT_FILE_APPEND;
	else
		token->type = OUT_FILE;
	token->args = get_args((*pre_token_list)->next, 1);
	*pre_token_list = (*pre_token_list)->next->next;
	if (token->args == NULL)
	{
		free(token);
		return (NULL);
	}
	return (token);
}

static t_token	*get_cmd_token(t_list **pre_token_list)
{
	t_token			*token;
	t_pre_token		*pre_token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = CMD;
	token->args = get_args(*pre_token_list, -1);
	pre_token = (t_pre_token *)(*pre_token_list)->content;
	while (pre_token && pre_token->type == TEXT)
	{
		*pre_token_list = (*pre_token_list)->next;
		if (*pre_token_list)
			pre_token = (t_pre_token *)(*pre_token_list)->content;
		else
			pre_token = NULL;
	}
	if (token->args == NULL)
	{
		free(token);
		return (NULL);
	}
	return (token);
}

static t_token	*get_pipe_token(t_list **pre_token_list)
{
	t_token		*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = PIPE;
	*pre_token_list = (*pre_token_list)->next;
	return (token);
}

t_list	*get_token_list(t_list *pre_token_list)
{
	t_pre_token	*pre_token;
	t_token		*token;
	t_list		*token_node;
	t_list		*token_list;

	token_list = NULL;
	while (pre_token_list)
	{
		pre_token = (t_pre_token *)pre_token_list->content;
		if (pre_token->type == REDIRECTION)
			token = get_redirection_token(&pre_token_list);
		else if (pre_token->type == TEXT)
			token = get_cmd_token(&pre_token_list);
		else
			token = get_pipe_token(&pre_token_list);
		token_node = ft_lstnew(token);
		if (token == NULL || token_node == NULL)
		{
			free(token_node);
			clear_token(token);
			ft_lstclear(&token_list, clear_token);
			return (NULL);
		}
		ft_lstadd_back(&token_list, token_node);
	}
	return (token_list);
}