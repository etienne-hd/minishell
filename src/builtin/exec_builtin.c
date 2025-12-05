/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 00:10:36 by ehode             #+#    #+#             */
/*   Updated: 2025/12/04 16:51:32 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "ft_printf.h"

int	exec_builtin(t_process *process, t_exec *exec, t_ctx *ctx)
{
	char	*builtin;
	int		exit_code;

	builtin = process->args[0];
	exit_code = 1;
	if (ft_strcmp(builtin, "echo") == 0)
		exit_code = builtin_echo(process, ctx);
	else if (ft_strcmp(builtin, "cd") == 0)
		exit_code = builtin_cd(process, ctx);
	else if (ft_strcmp(builtin, "pwd") == 0)
		exit_code = builtin_pwd(process, ctx);
	else if (ft_strcmp(builtin, "export") == 0)
		exit_code = builtin_export(process, ctx);
	else if (ft_strcmp(builtin, "unset") == 0)
		exit_code = builtin_unset(process, ctx);
	else if (ft_strcmp(builtin, "env") == 0)
		exit_code = builtin_env(process, ctx);
	else if (ft_strcmp(builtin, "exit") == 0)
		exit_code = builtin_exit(process, exec, ctx);
	return (exit_code);
}
