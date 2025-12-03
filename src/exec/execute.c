/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 22:41:36 by ehode             #+#    #+#             */
/*   Updated: 2025/12/03 00:58:35 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "exec.h"

void	execute(t_exec *exec, t_ctx *ctx)
{
	open_files(exec, ctx);
	close_files(exec);
	free_exec(&exec);
}