/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:43:30 by ncorrear          #+#    #+#             */
/*   Updated: 2025/12/03 17:07:29 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "exec.h"
#include "ft_printf.h"
#include <unistd.h>

int	echo(t_process *process)
{
	char	**args;
	size_t	i;
	int		is_n;
	int		fd;
	
	if (args == NULL)
		return (FAILURE);
	is_n = (args[1] && ft_strcmp(args[1], "-n") == 0);
	i += 1 + is_n;
	if (process->file_out)
		fd = process->file_out->fd;
	else
		fd = STDOUT_FILENO;
	while (args[i])
	{
		ft_dprintf(fd, "%s", args[i]);
		if (args[i + 1])
			ft_dprintf(fd, " ");
		i++;
	}
	return (SUCCESS);
}
