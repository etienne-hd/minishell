/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 15:10:09 by ehode             #+#    #+#             */
/*   Updated: 2025/12/03 02:00:30 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "ft_printf.h"
#include "libft.h"
#include "parsing.h"
#include "utils.h"
#include <stddef.h>

/**
 * @brief Special expand for all a scope ("expand" / 'no expand')
 *
 * @param scope Begining of the scope '\"' '\''
 * @param scope_end Pointer to the next same scope
 * @param ctx global context of minishell for variables
 * @return 
 */
static char	*expand_scope(char *scope, char *scope_end, t_ctx *ctx)
{
	char	scope_type;
	size_t	scope_length;
	char	*expanded_scope;

	scope_type = scope[0];
	scope++;
	scope_length = scope_end - scope;
	if (scope_type == '\"')
		expanded_scope = n_expand(scope, scope_length, ctx);
	else
		expanded_scope = ft_strndup(scope, scope_length);
	return (expanded_scope);
}

static int	scope_expand_utils(t_list **expanded_args, char	*current_arg,
	size_t *i, t_ctx *ctx)
{
	char	*scope_end;
	char	*current_expanded;
	size_t	expand_length;
	t_list	*last_arg;

	last_arg = ft_lstlast(*expanded_args);
	scope_end = ft_strchr(&current_arg[*i + 1], current_arg[*i]);
	current_expanded = expand_scope(&current_arg[*i], scope_end, ctx);
	if (current_expanded == NULL)
	{
		ft_lstclear(expanded_args, free);
		return (1);
	}
	expand_length = ft_strlen(current_expanded);
	if (bounded_join((char **)&last_arg->content, *i,
			current_expanded, scope_end + 1))
	{
		ft_lstclear(expanded_args, free);
		return (1);
	}
	*i += expand_length;
	return (0);
}

static int	outscope_expand_utils(t_list **expanded_args,
	char	*current_arg, size_t *i, t_ctx *ctx)
{
	char	*scope_end;
	char	*current_expanded;
	size_t	expand_length;
	t_list	*last_arg;

	last_arg = ft_lstlast(*expanded_args);
	scope_end = ft_find_first_address(3, ft_strchr(&current_arg[*i], '\''),
			ft_strchr(&current_arg[*i], '\"'),
			ft_strchr(&current_arg[*i], '\0'));
	current_expanded = n_expand(&current_arg[*i],
			scope_end - &current_arg[*i], ctx);
	if (current_expanded == NULL)
	{
		ft_lstclear(expanded_args, free);
		return (1);
	}
	expand_length = ft_strlen(current_expanded);
	if (bounded_join((char **)&last_arg->content, *i,
			current_expanded, scope_end))
	{
		ft_lstclear(expanded_args, free);
		return (1);
	}
	split_outscope(last_arg, i, expand_length);
	return (0);
}

/**
 * @brief expand a string and place a splitted element into a t_list
 *
 * @param arg string to expand and split
 * @param ctx global context of minishell for variables
 * @return 
 */
t_list	*expand_arg(char *arg, t_ctx *ctx)
{
	t_list	*expanded_args;
	t_list	*last_arg;
	size_t	i;
	char	*current_arg;

	expanded_args = ft_lstnew(arg);
	i = 0;
	last_arg = expanded_args;
	while (last_arg && ((char *)last_arg->content)[i])
	{
		current_arg = ((char *)last_arg->content);
		if ((current_arg[i] == '\'' || current_arg[i] == '\"'))
		{
			if (scope_expand_utils(&expanded_args, current_arg, &i, ctx))
				return (NULL);
		}
		else
		{
			if (outscope_expand_utils(&expanded_args, current_arg, &i, ctx))
				return (NULL);
		}
		last_arg = ft_lstlast(expanded_args);
	}
	return (expanded_args);
}

/**
 * @brief Expand all the arg list of the token and replace the list
 *
 * @param token token to expand
 * @param ctx global context for variables
 * @return 
 */
int	expand(t_token *token, t_ctx *ctx)
{
	t_list	*args;
	t_list	*new_args;
	t_list	*new_arg;
	char	*tmp;

	args = token->args;
	new_args = NULL;
	while (args)
	{
		tmp = ft_strdup(args->content);
		new_arg = NULL;
		if (tmp != NULL && handle_tilde(&tmp) == 0)
			new_arg = expand_arg(tmp, ctx);
		if (!new_arg || tmp == NULL)
		{
			free(tmp);
			ft_lstclear(&new_args, free);
			return (1);
		}
		ft_lstadd_back(&new_args, new_arg);
		args = args->next;
	}
	ft_lstclear(&token->args, free);
	token->args = new_args;
	return (0);
}
