/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 00:46:29 by ehode             #+#    #+#             */
/*   Updated: 2025/12/03 19:47:06 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	close_fd(int *fd)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
}

void	close_file(t_file *file)
{
	if (file->fd == PIPE_FD)
	{
		close_fd(&file->pipe[0]);
		close_fd(&file->pipe[1]);
	}
	else if (file->fd > 2)
		close_fd(&file->fd);
}

void	close_files(t_list *files)
{
	t_file	*file;

	while (files)
	{
		file = (t_file *)files->content;
		close_file(file);
		files = files->next;
	}
}
