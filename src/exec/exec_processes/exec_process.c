/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:54:15 by ehode             #+#    #+#             */
/*   Updated: 2025/12/04 16:52:10 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "error.h"
#include "exec.h"
#include "ft_printf.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

/**
 * @brief close the writing side of the process's file_in pipe, print error if
 * pipe failed
 *
 * @param process 
 * @return 
 */
static int	get_empty_in_pipe(t_process *process)
{
	if (pipe(process->file_in->pipe) == -1)
	{
		ft_dprintf(2, "Error\nPipe failed.\n");
		return (-1);
	}
	close_fd(&process->file_in->pipe[1]);
	return (process->file_in->pipe[0]);
}

/**
 * @brief prepare fd_in and fd_out based on process's files
 *
 * @param fd_in 
 * @param fd_out 
 * @param process 
 */
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
}

/**
 * @brief execute the given process in all possible case (builtin, pipe, etc..)
 *
 * @param process 
 * @param exec 
 * @param ctx 
 * @return 
 */
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
		exit(FAILURE);
	}
	dup2(fd_in, 0);
	dup2(fd_out, 1);
	close_files(exec->files);
	if (process->is_builtin)
		exec_builtin(process, exec, ctx);
	else if (execve(process->path, process->args, ctx->envp) == -1)
	{
		// TODO: CHECK IF IS IT A DIR OR PERMISSION NOT FOUND
		ft_dprintf(2, "minishell: %s: command not found\n", process->args[0],
			strerror(errno));
		free_exec(&exec);
		destroy_ctx(&ctx);
		exit(CMD_NOT_FOUND);
	}
	free_exec(&exec);
	destroy_ctx(&ctx);
	exit(SUCCESS);
}
