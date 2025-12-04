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

#include "ctx.h"
#include "exec.h"
#include "utils.h"
#include "error.h"
#include "ft_printf.h"
#include "libft.h"
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

/**
 * @brief Execute the changment of the working dir, display error message
 *
 * @param args 
 * @param i 
 * @param ctx 
 * @return 0 / 1 in fail case
 */
static int	cd_movement(char **args, size_t i, t_ctx *ctx)
{
	char	*path;

	if (i == 1)
		path = ft_dict_get(ctx->env, "HOME");
	else
		path = args[1];
	if (path == NULL)
	{
		ft_dprintf(STDERR_FILENO, "minishell: cd: << HOME >> not set\n");
		return (FAILURE);
	}
	if (chdir(path) == -1)
	{
		ft_dprintf(STDERR_FILENO, "minishell: cd: %s\n", strerror(errno));
		return (FAILURE);
	}
	return (SUCCESS);
}

/**
 * @brief Reset pwd env variable based on the old dir and the new one
 * (no usage of env pwd / old_pwd in it)
 *
 * @param pwd pwd before the move
 * @param ctx 
 * @return 
 */
static int	set_pwd_var(char *pwd, t_ctx *ctx)
{
	char		*tmp;

	tmp = ft_dict_get(ctx->env, "OLD_PWD");
	free(tmp);
	if (ft_dict_set(ctx->env, "OLD_PWD", pwd) == NULL)
		return (FAILURE);
	pwd = get_pwd();
	tmp = ft_dict_get(ctx->env, "PWD");
	free(tmp);
	if (ft_dict_set(ctx->env, "PWD", pwd) == NULL)
		return (FAILURE);
	return (0);
}

int	cd(t_process *process, t_ctx *ctx)
{
	char	**args;
	char	*tmp_set;
	size_t	i;

	args = process->args;
	tmp_set = get_pwd();
	if (args == NULL)
		return (FAILURE);
	i = 1;
	while (args[i])
		i++;
	if (i > 2)
	{
		ft_dprintf(STDERR_FILENO, "minishell: cd: too many arguments\n");
		return (CMD_BAD_USAGE);
	}
	if (cd_movement(args, i, ctx))
	{
		free(tmp_set);
		return (FAILURE);
	}
	if (set_pwd_var(tmp_set, ctx))
		return (FAILURE);
	return (SUCCESS);
}
