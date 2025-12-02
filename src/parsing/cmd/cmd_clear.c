/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:07:23 by ncorrear          #+#    #+#             */
/*   Updated: 2025/12/02 12:25:39 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <stddef.h>

static void	clear_args(char **args)
{
	size_t	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	clear_cmd(void *ptr)
{
	t_process	*cmd;

	cmd = (t_process *) ptr;
	free(cmd->path);
	if (cmd->args)
		clear_args(cmd->args);
	free(cmd);
}
