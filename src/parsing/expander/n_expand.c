/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_expand.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 15:43:46 by ehode             #+#    #+#             */
/*   Updated: 2025/11/30 19:57:55 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "ft_printf.h"
#include "libft.h"
#include "utils.h"
#include <stdlib.h>

static char	*expand_var(char *var, size_t *key_length, t_ctx *ctx)
{
	char	*key;
	char	*value;

	*key_length = 0;
	while (((ft_isalnum(var[*key_length]) || var[*key_length] == '_')
			&& var[*key_length - 1] != '?') || (var[*key_length] == '?'))
		(*key_length)++;
	key = ft_strndup(var, *key_length);
	if (!key)
		return (NULL);
	if (ft_strncmp(key, "?", 1) == 0)
		value = ft_itoa(ctx->status_code);
	else
	{
		value = ft_dict_get(ctx->env, key);
		if (!value)
			value = ft_strdup("");
		else
			value = ft_strdup(value);
	}
	free(key);
	return (value);
}

static int	n_expand_setter(char **s_expanded, size_t *i, size_t *n, t_ctx *ctx)
{
	size_t	key_length;
	size_t	value_length;
	char	*value;

	value = expand_var(&((*s_expanded)[*i + 1]), &key_length, ctx);
	if (value)
		value_length = ft_strlen(value);
	if (!value || bounded_join(s_expanded, *i,
			value, &((*s_expanded)[*i + key_length + 1])) == 1)
	{
		free(value);
		free(*s_expanded);
		return (1);
	}
	*n -= key_length;
	*i += value_length;
	return (0);
}

char	*n_expand(char *s, size_t n, t_ctx *ctx)
{
	size_t	i;
	char	*s_expanded;

	s_expanded = ft_strndup(s, n);
	if (!s_expanded)
		return (NULL);
	i = 0;
	while (n && s_expanded[i])
	{
		if (s_expanded[i] == '$' && (ft_isalnum(s_expanded[i + 1])
				|| s_expanded[i + 1] == '_' || s_expanded[i + 1] == '?'))
		{
			if (n_expand_setter(&s_expanded, &i, &n, ctx))
				return (NULL);
		}
		else
			i++;
		n--;
	}
	return (s_expanded);
}
