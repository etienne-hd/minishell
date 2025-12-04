/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 16:21:41 by ehode             #+#    #+#             */
/*   Updated: 2025/12/04 17:07:20 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "parsing.h"
#include "exec.h"
#include "ctx.h"
#include "libft.h" 
#include <stddef.h>

static int	is_valid_args(char **args)
{
	size_t	i;
	size_t	j;

	i = 1;
	j = 0;
	while (args[i])
	{
		j = 0;
		while (args[j])
		{
			if (!ft_isdigit(args[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	if (i == 2 && j == 0)
		return (0);
	return (1);
}

static int	get_argc(char **args)
{
	size_t	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	builtin_exit(t_process *process, t_exec *exec, t_ctx *ctx)
{
	int	exit_code;
	int	argc;

	argc = get_argc(process->args);
	if (is_valid_args(process->args) && argc > 2)
	{
		ft_dprintf(2, "bash: exit: too many arguments\n", process->args[0]);
		return (1);
	}
	if (ft_lstsize(exec->processes) == 1)
		printf("exit\n");
	if (!is_valid_args(process->args))
	{
		ft_dprintf(2, "bash: exit: %s: numeric argument required\n", process->args[1]);
		free_exec(&exec);
		destroy_ctx(&ctx);
		exit(2);
	}
	if (argc == 2)
		exit_code = ft_atoi(process->args[1]);
	else
		exit_code = 0;
	free_exec(&exec);
	destroy_ctx(&ctx);
	exit(exit_code);
}