/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:33:11 by ncorrear          #+#    #+#             */
/*   Updated: 2025/12/04 16:51:16 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "error.h"
#include "exec.h"
#include "libft.h"
#include <stddef.h>

int	builtin_unset(t_process *process, t_ctx *ctx)
{
	size_t	i;
	char	*value;

	if (process->args == NULL)
		return (FAILURE);
	i = 1;
	while (process->args[i])
	{
		value = ft_dict_get(ctx->env, process->args[i]);
		ft_dict_unset(ctx->env, process->args[i]);
		free(value);
		i++;
	}
	return (SUCCESS);
}
