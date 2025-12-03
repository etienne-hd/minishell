/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 22:29:18 by ehode             #+#    #+#             */
/*   Updated: 2025/12/03 01:16:13 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include "token.h"
#include <errno.h>
#include <fcntl.h>
#include <string.h>

int	open_file(t_file *file, t_ctx *ctx)
{
	char	*arg;

	if (ft_lstsize(file->args) > 1 || !file->args || !file->args->content)
	{
		file->fd = -1;
		return (1);
	}
	else if (file->fd == -42)
		return (1);
	arg = (char *)file->args->content;
	printf("DEBUG: OPENING %s\n", arg);
	if (file->type == IN_FILE)
		file->fd = open(arg, O_RDONLY, 0644);
	else if (file->type == IN_HERE_DOC)
		file->fd = here_doc(arg, ctx);
	else if (file->type == OUT_FILE)
		file->fd = open(arg, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	else
		file->fd = open(arg, O_APPEND | O_WRONLY | O_CREAT, 0644);
	if (file->fd == -1 && file->type != IN_HERE_DOC)
		printf("%s: %s\n", arg, strerror(errno));
	return (file->fd == -1);
}

static void	close_all_files_until_pipe(t_list *files)
{
	t_file	*file;

	while (files)
	{
		file = (t_file *)files->content;
		if (file->type == PIPE)
			break ;
		close_file(file);
		files = files->next;
	}
}

void	open_files(t_exec *exec, t_ctx *ctx)
{
	t_list	*begin_scope;
	t_list	*files;
	t_file	*file;
	int		skip;

	skip = 0;
	files = exec->files;
	begin_scope = files;
	while (files)
	{
		file = (t_file *)files->content;
		if (file->type == PIPE)
		{
			skip = 0;
			begin_scope = files;
		}
		else if (skip == 0 && open_file(file, ctx))
		{
			close_all_files_until_pipe(begin_scope);
			skip = 1;
		}
		files = files->next;
	}
}
