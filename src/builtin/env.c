/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:28:34 by ncorrear          #+#    #+#             */
/*   Updated: 2025/12/05 20:00:35 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "error.h"
#include "exec.h"
#include "libft.h"
#include <stddef.h>
#include <unistd.h>

int	builtin_env(t_process *process, t_ctx *ctx)
{
	t_dict_node	*env_dict;

	(void)process;
	if (ctx->env == NULL)
		return (FAILURE);
	env_dict = ctx->env->entry;
	while (env_dict)
	{
		if (env_dict->value != NULL)
			ft_printf("%s=%s\n", env_dict->key, (char *)env_dict->value);
		env_dict = env_dict->next;
	}
	return (SUCCESS);
}
