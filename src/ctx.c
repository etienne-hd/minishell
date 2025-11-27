/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 22:37:01 by ehode             #+#    #+#             */
/*   Updated: 2025/11/27 14:36:20 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ctx.h"
#include "libft.h"
#include <readline/readline.h>

/**
 * @brief free all dynamic allocation of ctx including sub struct
 * 
 * @param ctx 
 */
void	destroy_ctx(t_ctx **ctx)
{
	if (!*ctx)
		return ;
	if ((*ctx)->env)
		destroy_env(&(*ctx)->env);
	rl_clear_history();
	free(*ctx);
	*ctx = NULL;
}

/**
 * @brief init the ctx object and sub struct
 * 
 * @param argc 
 * @param argv 
 * @param envp 
 * @return t_ctx* 
 */
t_ctx	*init_ctx(int argc, char **argv, char **envp)
{
	t_ctx	*ctx;

	(void)argc;
	(void)argv;
	ctx = ft_calloc(1, sizeof(t_ctx));
	if (!ctx)
		return (NULL);
	ctx->env = load_env(envp);
	if (!ctx->env)
	{
		destroy_ctx(&ctx);
		return (NULL);
	}
	return (ctx);
}
