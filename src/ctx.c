/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 22:37:01 by ehode             #+#    #+#             */
/*   Updated: 2025/11/26 22:48:30 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ctx.h"
#include "libft.h"

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
	free(*ctx);
	*ctx = NULL;
}

/**
 * @brief get the ctx object with initialized env
 * 
 * @param argc 
 * @param argv 
 * @param envp 
 * @return t_ctx* 
 */
t_ctx	*get_ctx(int argc, char **argv, char **envp)
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
