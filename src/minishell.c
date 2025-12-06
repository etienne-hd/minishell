/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 16:53:30 by ehode             #+#    #+#             */
/*   Updated: 2025/12/06 16:35:31 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "exec.h"
#include "utils.h"
#include "parsing.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>

static t_ctx	*init_minishell(int argc, char **argv, char **envp)
{
	t_ctx	*ctx;

	rl_outstream = stderr;
	rl_catch_signals = 0;
	rl_catch_sigwinch = 0;
	ctx = init_ctx(argc, argv, envp);
	if (!ctx)
		safe_exit(&ctx, "Unable to init ctx.");
	return (ctx);
}

static void	minishell_routine(t_ctx *ctx)
{
	char		*input;
	t_exec		*exec;

	while (1)
	{
		set_default_signal_handler();
		input = get_input(ctx);
		set_signal_status_code(ctx);
		if (!input)
		{
			ft_dprintf(2, "exit\n");
			break ;
		}
		if (is_blank(input))
		{
			free(input);
			continue ;
		}
		add_history(input);
		exec = parse(input, ctx);
		if (exec)
			execute(exec, ctx);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_ctx		*ctx;
	u_int8_t	status_code;

	ctx = init_minishell(argc, argv, envp);
	minishell_routine(ctx);
	status_code = ctx->status_code;
	destroy_ctx(&ctx);
	return (status_code);
}
