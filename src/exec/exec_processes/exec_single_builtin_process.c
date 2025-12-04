/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_builtin_process.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:54:15 by ehode             #+#    #+#             */
/*   Updated: 2025/12/04 01:44:40 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "exec.h"
#include <string.h>
#include <unistd.h>

static void	get_fd(int *fd_in, int *fd_out, t_process *process)
{
	*fd_in = -1;
	*fd_out = -1;
	if (process->file_in)
		*fd_in = process->file_in->fd;
	else if (process->file_in == NULL)
		*fd_in = 0;
	if (process->file_out)
		*fd_out = process->file_out->fd;
	else if (process->file_out == NULL)
		*fd_out = 1;
}

/**
 * @brief execute a builtin command without fork (only for builtin)
 *
 * @param process 
 * @param exec 
 * @param ctx 
 */
void	exec_single_builtin_process(t_process *process,
		t_exec *exec, t_ctx *ctx)
{
	int	dup_stdin;
	int	dup_stdout;
	int	fd_in;
	int	fd_out;

	get_fd(&fd_in, &fd_out, process);
	dup_stdin = dup(0);
	dup_stdout = dup(1);
	dup2(fd_in, 0);
	dup2(fd_out, 1);
	ctx->status_code = exec_builtin(process, ctx);
	close_files(exec->files);
	dup2(dup_stdin, 0);
	dup2(dup_stdout, 1);
	close_fd(&dup_stdin);
	close_fd(&dup_stdout);
}
