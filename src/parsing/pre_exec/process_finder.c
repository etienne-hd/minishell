/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_finder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 11:27:56 by ncorrear          #+#    #+#             */
/*   Updated: 2025/12/02 18:53:47 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "libft.h"
#include "utils.h"
#include <stddef.h>
#include <unistd.h>

/**
 * @brief find the correct path to the command throught all paths
 *
 * @param all_paths 
 * @param command 
 * @return command_path / NULL if error
 */
static char	*find_path(char ***all_paths, char *command)
{
	size_t	i;
	char	*full_command;

	i = 0;
	while ((*all_paths)[i])
	{
		full_command = ft_strnjoin(3, (*all_paths)[i], "/", command);
		if (full_command == NULL || access(full_command, X_OK) == 0)
			return (full_command);
		free(full_command);
		i++;
	}
	full_command = ft_strdup(command);
	return (full_command);
}

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
	char	*full_command;

	if (command == NULL)
		return (NULL);
	full_command = ft_strdup(command);
	if (access(command, X_OK) == 0)
		return (full_command);
	path = ft_dict_get(ctx->env, "PATH");
	if (path == NULL)
		return (full_command);
	free(full_command);
	all_paths = ft_split(path, ':');
	if (all_paths == NULL)
		return (NULL);
	full_command = find_path(&all_paths, command);
	free_2d(&all_paths);
	return (full_command);
}
