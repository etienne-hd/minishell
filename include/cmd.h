/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 20:52:56 by ehode             #+#    #+#             */
/*   Updated: 2025/12/02 12:39:43 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

#include "ctx.h"
#include "parsing.h"

typedef struct s_cmd
{
	char	*path;
	char	**args;
	int		fd_in;
	int		fd_out;
	int		is_builtin;
}				t_cmd;

char	*get_cmd_path(char *command, t_ctx *ctx);
void	clear_cmd(void *ptr);
t_cmd	*token_to_command(t_token *token, t_ctx *ctx);

#endif
