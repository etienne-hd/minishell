/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 09:57:18 by ncorrear          #+#    #+#             */
/*   Updated: 2025/12/06 02:12:50 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "error.h"
#include <stddef.h>

char	*get_concat_value(char *value, char *key, t_ctx *ctx)
{
	char	*old;
	char	*tmp;

	old = ft_dict_get(ctx->env, key);
	if (old)
	{
		tmp = ft_strjoin(old, value);
		free(value);
		value = tmp;
	}
	return (value);
}

int	is_valide_export_mode(char *export_mode)
{
	if (export_mode[0] == '+')
	{
		if (export_mode[1] == '=')
			return (2);
	}
	else if (export_mode[0] == '=')
		return (1);
	else if (export_mode[0] == '\0')
		return (3);
	return (0);
}

int	check_error(char *key, char	**args, size_t i, size_t j)
{
	if (!key)
	{
		ft_dprintf(STDERR_FILENO, "minishell: export: System error\n");
		return (FAILURE);
	}
	if (is_valide_export_mode(&args[i][j]) == 0
		|| ft_strcmp(args[i], "=") == 0
		|| ft_strcmp(args[i], "+=") == 0)
	{
		ft_dprintf(STDERR_FILENO, "minishell: export: '%s': \
not a valid identifier\n", args[i]);
		return (FAILURE);
	}
	return (SUCCESS);
}
