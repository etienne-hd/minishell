/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:43:30 by ncorrear          #+#    #+#             */
/*   Updated: 2025/12/03 15:16:09 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "error.h"
#include "exec.h"
#include "ft_printf.h"

int	echo(t_process *process, t_ctx *ctx)
{
	char	**args;
	size_t	i;
	int		is_n;
	
	if (args == NULL)
		return (FAILURE);
	is_n = (args[1] && ft_strcmp(args[1], "-n") == 0);
	i += 1 + is_n;
	while (args[i])
	{
		ft_dprintf(process->file_out->fd, "%s", args[i]);
		if (args[i + 1])
			ft_dprintf(process->file_out->fd, " ");
		i++;
	}
	return (SUCCESS);
}
