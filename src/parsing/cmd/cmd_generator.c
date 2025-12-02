/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_generator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 11:38:45 by ncorrear          #+#    #+#             */
/*   Updated: 2025/12/02 12:48:03 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "exec.h"
#include "ft_printf.h"
#include "libft.h"
#include "parsing.h"
#include <stddef.h>
#include <stdlib.h>

static int	is_builtin(char *command)
{
	const char	*builtin[] = {"echo", "cd", "pwd", "export", "unset", "env",
		"exit", NULL};
	size_t		i;

	i = 0;
	while (builtin[i])
	{
		if (ft_strcmp(command, builtin[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

static void	fill_cmd_args(t_process *cmd, t_list *args_list)
{
	t_list	*current_arg;
	char	**args;
	size_t	nb_arg;

	current_arg = args_list;
	nb_arg = 0;
	while (current_arg)
	{
		current_arg = current_arg->next;
		nb_arg++;
	}
	args = calloc(nb_arg + 1, sizeof(char *));
	if (args != NULL)
	{
		current_arg = args_list;
		nb_arg = 0;
		while (current_arg)
		{
			args[nb_arg++] = current_arg->content;
			current_arg = current_arg->next;
		}
		args[nb_arg] = NULL;
	}
	cmd->args = args;
}

static int	fill_cmd_path(t_process *cmd, t_list *current_arg, t_ctx *ctx)
{
	if (is_builtin(current_arg->content))
	{
		cmd->is_builtin = 1;
		cmd->path = current_arg->content;
	}
	else
		cmd->path = get_cmd_path(current_arg->content, ctx);
	return (cmd->path == NULL);
}

t_process	*token_to_command(t_token *token, t_ctx *ctx)
{
	t_process	*cmd;
	t_list		*args;

	cmd = ft_calloc(1, sizeof(t_process));
	if (cmd == NULL)
		return (NULL);
	args = token->args;
	if (fill_cmd_path(cmd, args, ctx))
	{
		clear_cmd(cmd);
		ctx->status_code = 127;
		return (NULL);
	}
	fill_cmd_args(cmd, args);
	if (cmd->args == NULL)
	{
		clear_cmd(cmd);
		ctx->status_code = 1;
		return (NULL);
	}
	return (cmd);
}
