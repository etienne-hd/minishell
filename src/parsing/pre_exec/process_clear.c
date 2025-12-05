/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:07:23 by ncorrear          #+#    #+#             */
/*   Updated: 2025/12/05 03:54:21 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include "parsing.h"
#include "utils.h"
#include <stddef.h>

void	clear_file(void *ptr)
{
	t_file	*file;

	if (ptr == NULL)
		return ;
	file = (t_file *)ptr;
	if (file->args)
		ft_lstclear(&file->args, free);
	free(ptr);
}

void	clear_process_keep_args(void *ptr)
{
	t_process	*process;

	if (ptr == NULL)
		return ;
	process = (t_process *) ptr;
	free(process->path);
	free(process->args);
	free(process);
}

void	clear_process(void *ptr)
{
	t_process	*process;

	if (ptr == NULL)
		return ;
	process = (t_process *)ptr;
	free(process->path);
	if (process->args)
		free_2d(&process->args);
	free(process);
}
