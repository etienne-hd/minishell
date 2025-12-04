/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 17:01:24 by ncorrear          #+#    #+#             */
/*   Updated: 2025/12/04 01:18:52 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "error.h"
#include "ft_printf.h"
#include "libft.h"
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int	cd(t_process *process, t_ctx *ctx)
{
	char	**args;
	char	*path;
	size_t	i;

	args = process->args;
	if (args == NULL)
		return (FAILURE);
	i = 1;
	while (args[i])
		i++;
	if (i > 2)
	{
		ft_dprintf(STDERR_FILENO, "minishell: cd: too many arguments\n");
		return (FAILURE);
	}
	else if (i == 1)
		path = ft_dict_get(ctx->env, "HOME");
	else
		path = args[1];
	if (path == NULL || chdir(path) == -1)
	{
		ft_dprintf(STDERR_FILENO, "minishell: cd: %s", strerror(errno));
		return (FAILURE);
	}
	return (SUCCESS);
}
