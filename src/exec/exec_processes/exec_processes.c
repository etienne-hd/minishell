/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:54:15 by ehode             #+#    #+#             */
/*   Updated: 2025/12/04 23:15:53 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "exec.h"
#include "libft.h"
#include <stdlib.h>
#include <sys/wait.h>

/**
 * @brief wait all process of the process list from exec -> put the status_code
 * into the ctx
 *
 * @param exec 
 * @param ctx 
 */
static void	wait_processes(t_exec *exec, t_ctx *ctx)
{
	t_list		*processes;
	t_process	*current_process;
	int			stats;

	processes = exec->processes;
	while (processes)
	{
		current_process = (t_process *)processes->content;
		waitpid(current_process->pid, &stats, 0);
		processes = processes->next;
	}
	ctx->status_code = WEXITSTATUS(stats);
}

static void	close_pipe(t_process *process)
{
	if (process->file_out
		&& process->file_out->fd == PIPE_FD)
		close_fd(&process->file_out->pipe[1]);
	if (process->file_in
		&& process->file_in->fd == PIPE_FD)
		close_fd(&process->file_in->pipe[0]);
}

void	exec_processes(t_exec *exec, t_ctx *ctx)
{
	t_list		*processes;
	t_process	*current_process;

	processes = exec->processes;
	current_process = (t_process *)processes->content;
	if (ft_lstsize(exec->processes) == 1 && (current_process->is_builtin))
		exec_single_builtin_process(current_process, exec, ctx);
	else
	{
		while (processes)
		{
			current_process = (t_process *)processes->content;
			if (current_process->file_out
				&& current_process->file_out->fd == PIPE_FD)
				if (pipe(current_process->file_out->pipe) == -1)
				{
					ft_dprintf(2, "Error\nPipe failed.\n");
					break ;
				}
			current_process->pid = exec_process(current_process, exec, ctx);
			close_pipe(current_process);
			processes = processes->next;
		}
		wait_processes(exec, ctx);
	}
}
