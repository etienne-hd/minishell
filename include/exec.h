/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:46:43 by ehode             #+#    #+#             */
/*   Updated: 2025/12/01 22:50:18 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "libft.h"

typedef struct s_file
{
	t_list	*args;
	int		fd;
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
	t_file	file_in;
	t_file	file_out;
}				t_process;

#endif