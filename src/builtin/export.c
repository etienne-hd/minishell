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
#include <ctype.h>
#include <stddef.h>
#include <unistd.h>

static char	*get_concat_value(char *key, char *current_value, t_ctx *ctx)
{
	char	*tmp;

	tmp = ft_dict_get(ctx->env, key);
	if (tmp)
		tmp = ft_strjoin(tmp, current_value);
	else
		tmp = ft_strjoin("", current_value);
	free(current_value);
	return (tmp);
}

static int	get_type_export(char **args, char **key, size_t i, size_t *j)
{
	int	export_type;

	*key = ft_strndup(args[i], *j);
	if (*key == NULL)
		return (-1);
	export_type = 0;
	if (ft_strncmp("=", &args[i][*j], 1) == 0)
		export_type = 1;
	else if (ft_strncmp("=", &args[i][*j], 1) == 0)
		export_type = 2;
	*j += export_type;
	return (export_type);
}

int	export(t_process *process, t_ctx *ctx)
{
	char	*current_value;
	char	*key;
	size_t	i;
	size_t	j;
	int		export_type;

	i = 1;
	while (process->args[i])
	{
		key = NULL;
		current_value = NULL;
		export_type = 0;
		j = 0;
		while (isspace(process->args[i][j]) || process->args[i][j] == '_')
			j++;
		if (process->args[i][j] != '=' && process->args[i][j] != '+' && process->args[i][j] != '\0')
			ft_dprintf(STDERR_FILENO, "minishell: export: << %s >> : invalide key", process->args[i]);
		else if (process->args[i][j] != '\0')
		{
			export_type = get_type_export(process->args, &key, i, &j);
			if (export_type == 0)
				ft_dprintf(STDERR_FILENO, "minishell: export: << %s >> : invalide key", process->args[i]);
			else if (export_type == -1)
				return (FAILURE);
			else
			{
				current_value = ft_strdup(&process->args[i][j]);
				if (current_value && export_type == 2)
					current_value = get_concat_value(key, current_value, ctx);
				if (current_value == NULL)
				{
					free(key);
					return (FAILURE);
				}
				ft_dict_set(ctx->env, key, current_value);
			}
			free(key);
		}
		i++;
	}
	return (SUCCESS);
}
