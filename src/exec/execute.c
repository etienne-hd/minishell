/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 22:41:36 by ehode             #+#    #+#             */
/*   Updated: 2025/12/04 23:16:12 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "exec.h"
#include "utils.h"

void	execute(t_exec *exec, t_ctx *ctx)
{
	open_files(exec, ctx);
	if (g_signal != -21 && ft_lstsize(exec->processes) > 0)
		exec_processes(exec, ctx);
	close_files(exec->files);
	free_exec(&exec);
}
