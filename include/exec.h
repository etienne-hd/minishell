/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:46:43 by ehode             #+#    #+#             */
/*   Updated: 2025/12/02 18:42:59 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "libft.h"
#include "ctx.h"
#include "parsing.h"

typedef struct s_file
{
	t_token_type	type;
	t_list			*args;
	int				fd;
}				t_file;

typedef struct s_exec
{
	t_list	*processes;
	t_list	*files;
}				t_exec;

typedef struct s_process
{
	char	**args;
	char	*path;
	t_file	*file_in;
	t_file	*file_out;
	int		is_builtin;
}				t_process;

// Parsing Exec init
char		*get_cmd_path(char *command, t_ctx *ctx);
void		clear_process(void *ptr);
void		clear_process_keep_args(void *ptr);
t_process	*init_process(t_token *token, t_ctx *ctx);
t_exec		*init_exec(t_list *token_list, t_ctx *ctx);
int			is_redirection(t_token *token);

#endif
