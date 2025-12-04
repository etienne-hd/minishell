/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 17:16:57 by ncorrear          #+#    #+#             */
/*   Updated: 2025/12/03 17:35:32 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "exec.h"
#include "error.h"
#include "libft.h"
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

static char	*get_concat_value(char *key, char *current_value, t_ctx *ctx)
{
	char	*new_value;

	new_value = ft_dict_get(ctx->env, key);
	if (new_value)
		new_value = ft_strjoin(new_value, current_value);
	else
		new_value = ft_strjoin("", current_value);
	free(current_value);
	return (new_value);
}

static int	get_type_export(char **args, char **key, size_t i, size_t *j)
{
	int	export_type;

	*key = ft_strndup(args[i], *j);
	if (*key == NULL)
		return (-1);
	export_type = 0;
	if (j != 0 && ft_strncmp("=", &args[i][*j], 1) == 0)
		export_type = 1;
	else if (j != 0 && ft_strncmp("+=", &args[i][*j], 2) == 0)
		export_type = 2;
	else
		ft_dprintf(STDERR_FILENO,
			"minishell: export: << %s >> : invalide key\n", args[i]);
	*j += export_type;
	return (export_type);
}

static int	is_end_key(char c)
{
	if (!ft_isalnum(c) && c != '_')
		return (1);
	return (0);
}

static int	export_valid(size_t i, size_t j, char **args, t_ctx *ctx)
{
	int		export_type;
	char	*current_value;
	char	*tmp;
	char	*key;

	export_type = get_type_export(args, &key, i, &j);
	tmp = NULL;
	if (export_type > 0)
	{
		current_value = ft_strdup(&args[i][j]);
		if (current_value && export_type == 2)
			current_value = get_concat_value(key, current_value, ctx);
		if (current_value != NULL)
			tmp = ft_dict_get(ctx->env, key);
		free(tmp);
		if (current_value == NULL
			|| ft_dict_set(ctx->env, key, current_value) == NULL)
		{
			free(current_value);
			free(key);
			return (FAILURE);
		}
	}
	free(key);
	return (export_type == -1);
}

int	export(t_process *process, t_ctx *ctx)
{
	size_t	i;
	size_t	j;

	i = 1;
	while (process->args[i])
	{
		j = 0;
		while (!is_end_key(process->args[i][j]))
			j++;
		if (process->args[i][j] != '=' && process->args[i][j] != '+'
				&& process->args[i][j] != '\0')
			ft_dprintf(STDERR_FILENO,
				"minishell: export: << %s >> : invalide key\n",
				process->args[i]);
		else if (process->args[i][j] != '\0')
		{
			if (export_valid(i, j, process->args, ctx))
				return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}
