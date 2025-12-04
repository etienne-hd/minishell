/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:54:15 by ehode             #+#    #+#             */
/*   Updated: 2025/12/04 01:44:59 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "exec.h"
#include "libft.h"
#include <sys/wait.h>

void	wait_processes(t_exec *exec, t_ctx *ctx)
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
	ctx->status_code = stats;
}

void	exec_processes(t_exec *exec, t_ctx *ctx)
{
	t_list		*processes;
	t_process	*current_process;

	if (ft_lstsize(exec->processes) == 0)
		return ;
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
			{
				if (pipe(current_process->file_out->pipe) == -1)
				{
					// check if pipe failed
				}
			}
			exec_process(current_process, exec, ctx);
			if (current_process->file_out
				&& current_process->file_out->fd == PIPE_FD)
				close_fd(&current_process->file_out->pipe[1]);
			if (current_process->file_in
				&& current_process->file_in->fd == PIPE_FD)
				close_fd(&current_process->file_in->pipe[0]);
			processes = processes->next;
		}
		wait_processes(exec, ctx);
	}
}
