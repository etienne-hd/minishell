/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:21:41 by ehode             #+#    #+#             */
/*   Updated: 2025/12/06 10:22:06 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "exec.h"
#include "ctx.h"
#include "libft.h" 
#include "utils.h"
#include <stddef.h>
#include <stdint.h>

static int	is_valid_arg(char *arg)
{
	long long	number;
	int			sign;

	sign = 1;
	if (*arg == '-' || *arg == '+')
	{
		if (*arg == '-')
			sign = -1;
		arg++;
	}
	number = 0;
	while (ft_isdigit(*arg))
	{
		if ((sign == 1 && number > number * 10 + (*arg - '0'))
			|| (sign == -1 && number * sign
				< (number * 10 + (*arg - '0')) * sign))
			return (0);
		number = number * 10 + (*arg - '0');
		arg++;
	}
	return (*arg == 0);
}

static int	get_status_code(char *arg)
{
	uint8_t		status_code;
	int			sign;

	sign = 1;
	if (*arg == '-' || *arg == '+')
	{
		if (*arg == '-')
			sign = -1;
		arg++;
	}
	status_code = 0;
	while (ft_isdigit(*arg))
	{
		status_code = status_code * 10 + (*arg - '0');
		arg++;
	}
	return (status_code * sign);
}

int	builtin_exit(t_process *process, t_exec *exec, t_ctx *ctx)
{
	uint8_t	exit_code;
	int		argc;

	if (ft_lstsize(exec->processes) == 1)
		ft_dprintf(2, "exit\n");
	argc = get_argc(process->args);
	if (argc > 2 && is_valid_arg(process->args[1]))
	{
		ft_dprintf(2, "bash: exit: too many arguments\n");
		return (1);
	}
	if (argc >= 2 && !is_valid_arg(process->args[1]))
	{
		ft_dprintf(2, "bash: exit: %s: numeric argument required\n",
			process->args[1]);
		exit_code = 2;
	}
	else if (argc == 1)
		exit_code = ctx->status_code;
	else
		exit_code = get_status_code(process->args[1]);
	close_files(exec->files);
	free_exec(&exec);
	destroy_ctx(&ctx);
	exit(exit_code);
}
