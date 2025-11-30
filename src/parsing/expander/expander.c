/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 15:10:09 by ehode             #+#    #+#             */
/*   Updated: 2025/11/30 21:42:25 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "ft_printf.h"
#include "libft.h"
#include "parsing.h"
#include "utils.h"

char	*expand_scope(char *scope, char *scope_end, t_ctx *ctx)
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

t_list	*expand_arg(char *arg, t_ctx *ctx)
{
	t_list	*expanded_args;
	t_list	*last_arg;
	size_t	i;
	char 	*scope_end;
	char	*current_arg;
	char	*current_expanded;
	size_t	expand_length;

	// ARG = "Bonjour"
	//"Salu"t"$ARG Coucou"
	//"SalutBonjour Coucou"
	
	expanded_args = ft_lstnew(arg);
	if (expanded_args == NULL)
		return (NULL);
	i = 0;
	last_arg = expanded_args;
	while (((char *)last_arg->content)[i])
	{
		current_arg = ((char *)last_arg->content);
		// INSIDE SCOPE
		if ((current_arg[i] == '\'' || current_arg[i] == '\"'))
		{
			scope_end = ft_strchr(&current_arg[i + 1], current_arg[i]);
			current_expanded = expand_scope(&current_arg[i], scope_end, ctx);
			expand_length = ft_strlen(current_expanded);
			if (bounded_join((char **)&last_arg->content, i, current_expanded, scope_end + 1))
				; // FREEE
			i += expand_length;
		}
		// OUTSIDE SCOPE
		else
		{
			scope_end = ft_find_first_address(3, ft_strchr(&current_arg[i], '\''), 
				ft_strchr(&current_arg[i], '\"'), ft_strchr(&current_arg[i], '\0'));
			current_expanded = n_expand(&current_arg[i], scope_end - &current_arg[i], ctx);
			expand_length = ft_strlen(current_expanded);
			if (bounded_join((char **)&last_arg->content, i, current_expanded, scope_end))
				; // FREEE
			split_outscope(last_arg, &i, expand_length);
		}
		// ajouter a la lst 
		last_arg = ft_lstlast(expanded_args);
	}
	return (expanded_args);
}

int	expand(t_token *token, t_ctx *ctx)
{
	t_list	*args;
	t_list	*new_args;
	t_list	*new_arg;

	args = token->args;
	new_args = NULL;
	while (args)
	{
		new_arg = expand_arg(args->content, ctx);
		if (!new_arg)
			;// FAIL
		ft_lstadd_back(&new_args, new_arg);
		args = args->next;
	}
	ft_lstclear(&token->args, clear_arg);
	token->args = new_args;
	return (0);
}
