/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:46:43 by ehode             #+#    #+#             */
/*   Updated: 2025/12/04 01:02:53 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# define PIPE_FD -42

#include "libft.h"
#include "ctx.h"
#include "token.h"

typedef struct s_file
{
	t_token_type	type;
	t_list			*args;
	int				fd;
	int				pipe[2];
}				t_file;

typedef struct s_exec
{
	t_list	*processes;
	t_list	*files;
	t_ctx	*ctx;
}				t_exec;

typedef struct s_process
{
	char	**args;
	char	*path;
	t_file	*file_in;
	t_file	*file_out;
	int		is_builtin;
	int		pid;
}				t_process;

// Exec
void		execute(t_exec *exec, t_ctx *ctx);
void		free_exec(t_exec **exec);
void		exec_processes(t_exec *exec, t_ctx *ctx);
int			exec_process(t_process *process, t_exec *exec, t_ctx *ctx);
void		exec_single_builtin_process(t_process *process,
					t_exec *exec, t_ctx *ctx);

// File
void		close_fd(int *fd);
void		close_file(t_file *file);
void		close_files(t_list *files);
int			open_file(t_file *file, t_ctx *ctx);
void		open_files(t_exec *exec, t_ctx *ctx);
int			here_doc(char *delimiter, t_ctx *ctx);

// BuiltIn
int			exec_builtin(t_process *process, t_ctx *ctx);
int			echo(t_process *process, t_ctx *ctx);
int			cd(t_process *process, t_ctx *ctx);
int			pwd(t_process *process, t_ctx *ctx);
int			export(t_process *process, t_ctx *ctx);
int			unset(t_process *process, t_ctx *ctx);
int			env(t_process *process, t_ctx *ctx);

#endif
