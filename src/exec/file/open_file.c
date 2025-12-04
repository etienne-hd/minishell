/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 22:29:18 by ehode             #+#    #+#             */
/*   Updated: 2025/12/04 22:18:58 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "ft_printf.h"
#include "libft.h"
#include "token.h"
#include "utils.h"
#include <errno.h>
#include <fcntl.h>
#include <string.h>

/**
 * @brief Open the given file and set his fd
 *
 * @param file 
 * @param ctx 
 * @return 0 / 1 if open failed
 */
int	open_file(t_file *file, t_ctx *ctx)
{
	char	*arg;

	if (ft_lstsize(file->args) > 1 || !file->args || !file->args->content)
	{
		ft_dprintf(2, "minishell: ambiguous redirect\n",
			(char *)file->args->content);
		file->fd = -1;
		return (1);
	}
	else if (file->fd == PIPE_FD)
		return (1);
	arg = (char *)file->args->content;
	if (file->type == IN_FILE)
		file->fd = open(arg, O_RDONLY, 0644);
	else if (file->type == IN_HERE_DOC)
		file->fd = here_doc(arg, file->here_doc_to_expand, ctx);
	else if (file->type == OUT_FILE)
		file->fd = open(arg, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	else
		file->fd = open(arg, O_APPEND | O_WRONLY | O_CREAT, 0644);
	if (file->fd == -1 && file->type != IN_HERE_DOC)
		ft_dprintf(2, "%s: %s\n", arg, strerror(errno));
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

/**
 * @brief Open all the file in files of the exec at once (pipe excluded)
 *
 * @param exec 
 * @param ctx 
 */
void	open_files(t_exec *exec, t_ctx *ctx)
{
	t_list	*begin_scope;
	t_list	*files;
	t_file	*file;
	int		skip;

	skip = 0;
	files = exec->files;
	begin_scope = files;
	while (files && g_signal != -21)
	{
		file = (t_file *)files->content;
		if (file->type == PIPE)
		{
			skip = 0;
			begin_scope = files;
		}
		else if (skip == 0 && open_file(file, ctx))
		{
			ctx->status_code = 1;
			close_all_files_until_pipe(begin_scope);
			skip = 1;
		}
		files = files->next;
	}
}
