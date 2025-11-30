/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 10:28:32 by ncorrear          #+#    #+#             */
/*   Updated: 2025/11/30 13:53:54 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "ft_printf.h"
#include "libft.h"
#include "parsing.h"
#include "utils.h"
#include <stddef.h>

static	int	is_special_var(char c)
{
	if (c == '~' || c == '?')
		return (1);
	return (0);
}

static char	*get_special_var_content(char	*key, t_ctx	*ctx)
{
	char		*var_content;
	t_dict_node	*node;

	if (ft_strcmp(key, "$~") == 0)
	{
		node = ft_dict_get(ctx->env, "HOME");
		if (node != NULL)
			return (node->value);
	}
	else if (ft_strcmp(key, "$?") == 0)
	{
		var_content = ft_ulltoa(ctx->status_code);
		return (var_content);
	}
	return ("");
}

static int	replace_var(char **expanded_arg, char *key, t_ctx *ctx, int is_special)
{
	char		*tmp;
	t_dict_node	*var;
	char		*var_content;

	var = ft_dict_get_node(ctx->env, &key[1]);
	if (is_special)
		var_content = get_special_var_content(key, ctx);
	else if (var == NULL)
		var_content = "";
	else
		var_content = var->value;
	tmp = ft_replace(*expanded_arg, key, var_content);
	free(*expanded_arg);
	*expanded_arg = tmp;
	return (ft_strlen(var_content));
}

// Replace after index + outside scope
char	*get_expanded_arg(char	*arg, t_ctx *ctx)
{
	char		*expanded_arg;
	char		*key;
	int			i;
	int			j;
	int			is_special;

	i = 0;
	expanded_arg = ft_strdup(arg);
	while (expanded_arg[i])
	{
		if (expanded_arg[i] == '$')
		{
			j = 1;
			is_special = 0;
			while (ft_isalnum(expanded_arg[i + j]) || expanded_arg[i + j] == '_')
				j++;
			if (j == 1)
				is_special = is_special_var(expanded_arg[i + j]);
			j += is_special;
			if (j != 1)
			{
				key = ft_strndup(&expanded_arg[i], j);
				i += replace_var(&expanded_arg, key, ctx, is_special) - 1;
				free(key);
			}
		}
		i++;
	}
	return (expanded_arg);
}

// t_token	*expand_token(t_token *token, t_ctx ctx)
// {
// 	t_list	*current_arg;
//
// 	current_arg = token->args;
// 	while (current_arg)
// 	{
// 		current_arg = current_arg->next;
// 	}
// 	return (token);
// }
