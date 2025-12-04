/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:33:11 by ncorrear          #+#    #+#             */
/*   Updated: 2025/12/03 15:16:11 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "error.h"
#include "exec.h"
#include "libft.h"
#include <stddef.h>

int	unset(t_process *process, t_ctx *ctx)
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
