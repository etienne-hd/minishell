/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:09:04 by ncorrear          #+#    #+#             */
/*   Updated: 2025/12/03 20:12:44 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "utils.h"
#include "error.h"
#include "exec.h"
#include <stddef.h>
#include <unistd.h>

int	pwd(t_process *process, t_ctx ctx)
{
	char	**args;
	char	*pwd;
	
	args = process->args;
	if (args == NULL)
		return (FAILURE);
	pwd = get_pwd();
	if (pwd == NULL)
		return (FAILURE);
	if (process->file_out)
		ft_dprintf(process->file_out->fd ,"%s\n", pwd);
	else
		ft_dprintf(STDOUT_FILENO ,"%s\n", pwd);
	free(pwd);
	return (SUCCESS);
}
