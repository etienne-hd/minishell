/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:28:34 by ncorrear          #+#    #+#             */
/*   Updated: 2025/12/04 01:16:55 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "error.h"
#include "exec.h"
#include "ft_printf.h"
#include "libft.h"
#include <stddef.h>
#include <unistd.h>

int	env(t_process *process, t_ctx *ctx)
{
	t_dict_node	*env_dict;

	(void)process;
	if (ctx->env == NULL)
		return (FAILURE);
	env_dict = ctx->env->entry;
	while (env_dict)
	{
		printf("%s=%s\n",env_dict->key, (char *)env_dict->value);
		env_dict = env_dict->next;
	}
	return (SUCCESS);
}
