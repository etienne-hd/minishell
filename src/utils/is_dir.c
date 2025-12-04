/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 18:45:21 by ehode             #+#    #+#             */
/*   Updated: 2025/12/04 19:07:18 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <errno.h>
#include <asm-generic/errno-base.h>
#include <dirent.h>
#include <string.h>

int	is_dir(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir == NULL && errno == EACCES)
		return (1);
	if (dir == NULL)
		return (0);
	closedir(dir);
	return (1);
}