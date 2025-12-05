/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_builtin_process.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:54:15 by ehode             #+#    #+#             */
/*   Updated: 2025/12/05 20:00:25 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "exec.h"
#include "ft_printf.h"
#include "libft.h"
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

static int	add_to_files(int fd, t_exec *exec)
{
	t_file	*file;
	t_list	*file_list;

	file = ft_calloc(1, sizeof(t_file));
	if (!file)
	{
		close(fd);
		ft_dprintf(2, "Error\nAllocation failed.\n");
		return (1);
	}
	file->fd = fd;
	file_list = ft_lstnew(file);
	if (!file_list)
	{
		close(fd);
		ft_dprintf(2, "Error\nAllocation failed.\n");
		free(file);
		return (1);
	}
	ft_lstadd_back(&exec->files, file_list);
	return (0);
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
	if (add_to_files(dup_stdin, exec))
		return ;
	dup_stdout = dup(1);
	if (add_to_files(dup_stdout, exec))
		return ;
	if (fd_in != 0)
		dup2(fd_in, 0);
	if (fd_out != 1)
		dup2(fd_out, 1);
	ctx->status_code = exec_builtin(process, exec, ctx);
	dup2(dup_stdin, 0);
	dup2(dup_stdout, 1);
	close_files(exec->files);
	close_fd(&dup_stdin);
	close_fd(&dup_stdout);
}
