/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 00:10:44 by ehode             #+#    #+#             */
/*   Updated: 2025/12/06 16:49:46 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "ft_printf.h"
#include <readline/readline.h>

int	g_signal = -1;

void	set_signal_status_code(t_ctx *ctx)
{
	if (g_signal == -1)
		return ;
	if (g_signal == 2)
		ctx->status_code = 130;
	g_signal = -1;
}

void	process_handle_signal(int sig)
{
	ft_printf("\n");
	g_signal = sig;
}

void	heredoc_handle_signal(int sig)
{
	ft_printf("^C");
	rl_on_new_line();
	rl_replace_line("", 0);
	close(0);
	g_signal = sig;
}

void	default_handle_signal(int sig)
{
	if (sig == 2)
	{
		ft_printf("^C\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_signal = sig;
}
