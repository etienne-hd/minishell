/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 21:17:15 by ehode             #+#    #+#             */
/*   Updated: 2025/11/26 22:49:55 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

/**
 * @brief expand home path ~ -> /home/user
 * 
 * @param path 
 * @param env 
 * @return char* 
 */
char	*path_tilde_expand(char *path, t_dict *env)
{
	char	*tilde_expand;
	char	*home_path;

	home_path = ft_dict_get(env, "HOME");
	if (!home_path)
		return (NULL);
	if (ft_strncmp(path, "~", 1) == 0)
	{
		tilde_expand = ft_strjoin(home_path, path + 1);
		if (!tilde_expand)
			return (NULL);
		return (tilde_expand);
	}
	return (NULL);
}

/**
 * @brief collapse home path /home/user -> ~
 * 
 * @param path 
 * @param env 
 * @return char* 
 */
char	*path_tilde_collapse(char *path, t_dict *env)
{
	char	*collapse_path;
	char	*home_path;
	size_t	home_path_len;

	home_path = ft_dict_get(env, "HOME");
	if (!home_path)
		return (NULL);
	home_path_len = ft_strlen(home_path);
	if (ft_strncmp(path, home_path, home_path_len) == 0)
	{
		collapse_path = ft_strjoin("~", path + home_path_len);
		if (!collapse_path)
			return (NULL);
		return (collapse_path);
	}
	return (NULL);
}
