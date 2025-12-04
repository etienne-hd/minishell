/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 00:10:36 by ehode             #+#    #+#             */
/*   Updated: 2025/12/04 00:47:15 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "ft_printf.h"

int	exec_builtin(t_process *process, t_ctx *ctx)
{
	char	*builtin;
	int		exit_code;

	builtin = process->args[0];
	exit_code = 1;
	if (ft_strcmp(builtin, "echo") == 0)
		exit_code = echo(process, ctx);
	else if (ft_strcmp(builtin, "cd") == 0)
		exit_code = cd(process, ctx);
	else if (ft_strcmp(builtin, "pwd") == 0)
		exit_code = pwd(process, ctx);
	else if (ft_strcmp(builtin, "export") == 0)
		exit_code = export(process, ctx);
	else if (ft_strcmp(builtin, "unset") == 0)
		exit_code = unset(process, ctx);
	else if (ft_strcmp(builtin, "env") == 0)
		exit_code = env(process, ctx);
	else if (ft_strcmp(builtin, "exit") == 0)
		ft_dprintf(2, "Error\n%s not implemented!\n", builtin);
	return (exit_code);
}
