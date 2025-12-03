/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 16:53:30 by ehode             #+#    #+#             */
/*   Updated: 2025/12/03 02:14:11 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "exec.h"
#include "utils.h"
#include "parsing.h"
#include "signal.h"
#include <readline/history.h>
#include <readline/readline.h>

int	main(int argc, char **argv, char **envp)
{
	t_ctx	*ctx;
	char	*input;
	int		status_code;
	t_exec	*exec;

    signal(SIGINT, handle_signal);
    signal(SIGQUIT, handle_signal);
	ctx = init_ctx(argc, argv, envp);
	if (!ctx)
		safe_exit(&ctx, "Unable to init ctx.");
	while (1)
	{
		input = get_input(ctx);
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (is_blank(input))
			continue ;
		add_history(input);
		exec = parse(input, ctx);
		if (exec)
			execute(exec, ctx);
	}
	status_code = ctx->status_code;
	destroy_ctx(&ctx);
	return (status_code);
}

