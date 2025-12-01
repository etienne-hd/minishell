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

/**
 * @brief get a string that start on '$'and return a new one allocated 
 * with replaced variable ($HOME -> "/home/user")
 *
 * @param var string that start on the '$' of the var
 * @param key_length pointer where store the key length
 * @param ctx global context of minishell for ($?)
 * @return allocated expanded var / NULL if failed
 */
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

/**
 * @brief 
 *
 * @param s_expanded 
 * @param i 
 * @param n 
 * @param ctx 
 * @return 
 */
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
		free(*s_expanded);
		return (1);
	}
	*n -= key_length;
	*i += value_length;
	return (0);
}

/**
 * @brief Expand 'n' char from a string (expand even if n = 1 and s = "$PATH"
 * -> n based on '$')
 *
 * @param s String to expand
 * @param n number of char to look for expand
 * @param ctx global context of minishel for error code
 * @return new chain allocated / NULL if malloc failed
 */
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
