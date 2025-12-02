/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_finder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 11:27:56 by ncorrear          #+#    #+#             */
/*   Updated: 2025/12/02 12:51:33 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "libft.h"
#include <stddef.h>
#include <unistd.h>

/**
 * @brief return the valid absolute path of a command
 *
 * @param command command name / full path
 * @param ctx global context of minishell to get PATH
 * @return command path / NULL if error or not find
 */
char	*get_cmd_path(char *command, t_ctx *ctx)
{
	char	*path;
	char	**all_paths;
	size_t	i;
	char	*full_command;

	if (command == NULL)
		return (NULL);
	full_command = ft_strdup(command);
	if (access(command, X_OK) == 0)
		return (full_command);
	path = ft_dict_get(ctx->env, "PATH");
	if (path == NULL)
		return (command);
	all_paths = ft_split(path, ':');
	if (all_paths == NULL)
		return (NULL);
	i = 0;
	while (all_paths[i])
	{
		full_command = ft_strnjoin(3, all_paths[i], "/", command);
		if (full_command == NULL || access(full_command, X_OK) == 0)
			return (full_command);
		free(full_command);
		i++;
	}
	full_command = ft_strdup(command);
	return (full_command);
}
