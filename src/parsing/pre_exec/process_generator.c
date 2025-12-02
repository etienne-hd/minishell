/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_generator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 11:38:45 by ncorrear          #+#    #+#             */
/*   Updated: 2025/12/02 16:33:33 by ehode            ###   ########.fr       */
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

static void	fill_process_args(t_process *cmd, t_list *args_list)
{
	t_list	*current_arg;
	char	**args;
	size_t	nb_arg;

	current_arg = args_list;
	nb_arg = ft_lstsize(args_list);
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

t_process	*init_process(t_token *token, t_ctx *ctx)
{
	t_process	*process;
	t_list		*args;

	process = ft_calloc(1, sizeof(t_process));
	if (process == NULL)
		return (NULL);
	args = token->args;
	if (fill_cmd_path(process, args, ctx))
	{
		clear_process(process);
		ctx->status_code = 127;
		return (NULL);
	}
	fill_process_args(process, args);
	if (process->args == NULL)
	{
		clear_process(process);
		ctx->status_code = 1;
		return (NULL);
	}
	process->file_out = NULL;
	process->file_in = NULL;
	return (process);
}
