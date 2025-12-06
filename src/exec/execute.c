/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 22:41:36 by ehode             #+#    #+#             */
/*   Updated: 2025/12/06 17:18:53 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "exec.h"
#include "utils.h"

void	execute(t_exec *exec, t_ctx *ctx)
{
	g_signal = -1;
	open_files(exec, ctx);
	if (g_signal != 2 && ft_lstsize(exec->processes) > 0)
	{
		set_out_process_signal_handler();
		exec_processes(exec, ctx);
	}
	close_files(exec->files);
	free_exec(&exec);
}
