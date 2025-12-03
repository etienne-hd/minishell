/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 00:46:29 by ehode             #+#    #+#             */
/*   Updated: 2025/12/03 01:18:39 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	close_file(t_file *file)
{
	if (file->fd > 2)
	{
		if (file->args)
			printf("DEBUG: CLOSING %s\n", (char *)file->args->content);
		close(file->fd);
		file->fd = -1;
	}
}

void	close_files(t_exec *exec)
{
	t_list	*files;
	t_file	*file;

	files = exec->files;
	while (files)
	{
		file = (t_file *)files->content;
		close_file(file);
		files = files->next;
	}
}
