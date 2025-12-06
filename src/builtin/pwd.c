/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:09:04 by ncorrear          #+#    #+#             */
/*   Updated: 2025/12/05 20:00:57 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "error.h"
#include "exec.h"
#include <stddef.h>
#include <unistd.h>

int	builtin_pwd(t_process *process, t_ctx *ctx)
{
	char	**args;
	char	*pwd;

	(void)ctx;
	args = process->args;
	if (args == NULL)
		return (FAILURE);
	pwd = get_pwd();
	if (pwd == NULL)
		return (FAILURE);
	ft_printf("%s\n", pwd);
	free(pwd);
	return (SUCCESS);
}
