/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:54:15 by ehode             #+#    #+#             */
/*   Updated: 2025/12/03 22:27:51 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "exec.h"
#include "ft_printf.h"
#include <string.h>
#include <errno.h>
#include <unistd.h>

static int	get_empty_in_pipe(t_process *process)
{
	if (pipe(process->file_in->pipe) == -1)
		;// IF PIPE FAILED
	close_fd(&process->file_in->pipe[1]);
	return (process->file_in->pipe[0]);
}

static void	get_fd(int *fd_in, int *fd_out, t_process *process)
{
	*fd_in = -1;
	*fd_out = -1;
	if (process->file_in && process->file_in->fd == PIPE_FD)
	{
		if (process->file_in->pipe[0] != -1)
			*fd_in = process->file_in->pipe[0];
		else
			*fd_in = get_empty_in_pipe(process);
	}
	else if (process->file_in)
		*fd_in = process->file_in->fd;
	else if (process->file_in == NULL)
		*fd_in = 0;
	if (process->file_out && process->file_out->fd == PIPE_FD)
	{
		*fd_out = process->file_out->pipe[1];
	}
	else if (process->file_out)
		*fd_out = process->file_out->fd;
	else if (process->file_out == NULL)
		*fd_out = 1;
	printf("DEBUG: %s; FD_IN %d (%p); FD_OUT %d (%p)\n", process->path, *fd_in, process->file_in, *fd_out, process->file_out);
}

int	exec_process(t_process *process, t_exec *exec, t_ctx *ctx)
{
	int	pid;
	int	fd_in;
	int	fd_out;

	pid = fork();
	if (pid == -1)
		; // FORK FAILED
	else if (pid != 0)
		return (pid);
	get_fd(&fd_in, &fd_out, process);
	if (fd_in == -1 || fd_out == -1)
	{
		close_files(exec->files);
		free_exec(&exec);
		destroy_ctx(&ctx);
		exit(1);
	}
	dup2(fd_in, 0);
	dup2(fd_out, 1);
	close_files(exec->files);
	if (execve(process->path, process->args, ctx->envp) == -1)
	{
		ft_dprintf(2, "%s: command not found\n", process->args[0], strerror(errno));
		exit(127);
	}
	free_exec(&exec);
	destroy_ctx(&ctx);
	exit(1);
}
