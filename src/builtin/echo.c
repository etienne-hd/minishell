/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:43:30 by ncorrear          #+#    #+#             */
/*   Updated: 2025/12/05 19:55:12 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "exec.h"
#include <unistd.h>

int	builtin_echo(t_process *process, t_ctx *ctx)
{
	char	**args;
	size_t	i;
	int		is_n;

	(void)ctx;
	i = 1;
	args = process->args;
	if (args == NULL)
		return (FAILURE);
	is_n = 0;
	while (args[i + is_n] && ft_strncmp(args[i + is_n], "-n", 2) == 0)
		is_n++;
	i += is_n;
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (!is_n)
		ft_printf("\n");
	return (SUCCESS);
}
