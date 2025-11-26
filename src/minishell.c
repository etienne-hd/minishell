/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 16:53:30 by ehode             #+#    #+#             */
/*   Updated: 2025/11/26 21:45:56 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"
#include "utils.h"
#include "libft.h"
#include <stdio.h>

void	destroy_ctx(t_ctx **ctx)
{
	if (!*ctx)
		return ;
	if ((*ctx)->env)
		destroy_env(&(*ctx)->env);
	free(*ctx);
	*ctx = NULL;
}

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

int	main(int argc, char **argv, char **envp)
{
	t_ctx	*ctx;

	ctx = get_ctx(argc, argv, envp);
	if (!ctx)
		return (1);
	get_input(ctx);
	destroy_ctx(&ctx);
}
