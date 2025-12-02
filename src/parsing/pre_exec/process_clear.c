/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:07:23 by ncorrear          #+#    #+#             */
/*   Updated: 2025/12/02 18:30:44 by ehode            ###   ########.fr       */
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

	file = (t_file *)ptr;
	ft_lstclear(&file->args, clear_arg);
	free(ptr);
}

void	clear_process_keep_args(void *ptr)
{
	t_process	*process;

	process = (t_process *) ptr;
	free(process->path);
	free(process->args);
	free(process);
}

void	clear_process(void *ptr)
{
	t_process	*process;

	process = (t_process *) ptr;
	free(process->path);
	if (process->args)
		free_2d(&process->args);
	free(process);
}
