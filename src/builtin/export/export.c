/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 14:09:18 by ncorrear          #+#    #+#             */
/*   Updated: 2025/12/05 10:19:23 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "exec.h"
#include "ctx.h"
#include "libft.h"
#include <stddef.h>
#include <unistd.h>

static int	add_to_dict(char *value, char *key, t_ctx *ctx)
{
	char	*tmp;

	tmp = ft_dict_get(ctx->env, key);
	if (value == NULL && tmp == NULL)
	{
		free(tmp);
		if (ft_dict_set(ctx->env, key, value) == NULL)
		{
			free(key);
			free(value);
			return (FAILURE);
		}
	}
	else if (value != NULL && ft_dict_set(ctx->env, key, value) == NULL)
	{
		free(key);
		free(value);
		return (FAILURE);
	}
	if (value != NULL)
		free(tmp);
	return (SUCCESS);
}

static int	set_val_export(char *post_key, char *key, t_ctx *ctx)
{
	char	*value;
	int		mode;
	size_t	i;

	mode = is_valide_export_mode(post_key);
	if (mode == 3)
	{
		mode = add_to_dict(NULL, key, ctx);
		return (mode);
	}
	i = mode - 1;
	while (post_key[i])
		i++;
	value = ft_strndup(&post_key[mode], i);
	if (mode == 2)
		value = get_concat_value(value, key, ctx);
	if (add_to_dict(value, key, ctx))
		return (FAILURE);
	return (SUCCESS);
}

static int	export_vars(char **args, t_ctx *ctx)
{
	size_t	i;
	size_t	j;
	int		error;
	char	*key;

	i = 0;
	error = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j] && (ft_isalnum(args[i][j]) || args[i][j] == '_'))
			j++;
		key = ft_strndup(args[i], j);
		if (check_error(key, args, i, j))
			error = FAILURE;
		else
			set_val_export(&args[i][j], key, ctx);
		free(key);
		i++;
	}
	return (error);
}

int	export(t_process *process, t_ctx *ctx)
{
	char	**args;
	size_t	i;
	int		error;

	args = process->args;
	if (!args)
		return (FAILURE);
	i = 0;
	error = SUCCESS;
	while (args[i])
		i++;
	if (i == 1)
		print_export(ctx->env);
	else
		error = export_vars(&args[1], ctx);
	return (error);
}
