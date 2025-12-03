/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:28:34 by ncorrear          #+#    #+#             */
/*   Updated: 2025/12/03 15:16:07 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "error.h"
#include "exec.h"
#include "ft_printf.h"
#include "libft.h"
#include <stddef.h>

int	env(t_process *process, t_ctx *ctx)
{
	t_dict_node	*env_dict;

	if (ctx->env == NULL)
		return (FAILURE);
	env_dict = ctx->env->entry;
	while (env_dict)
	{
		ft_printf("%s=%s\n",env_dict->key, env_dict->value);
		env_dict = env_dict->next;
	}
	return (SUCCESS);
}
