/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:43:49 by ncorrear          #+#    #+#             */
/*   Updated: 2025/12/04 23:49:08 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include "utils.h"
#include <stddef.h>

static int	remove_scope(char **arg, size_t *i)
{
	char	*end_scope;
	char	*tmp;
	size_t	length;

	end_scope = ft_strchr(&(*arg)[*i + 1], (*arg)[*i]);
	tmp = ft_strndup(&(*arg)[*i + 1], end_scope - &(*arg)[*i + 1]);
	if (!tmp)
		return (1);
	length = ft_strlen(tmp);
	if (bounded_join(arg, &(*arg)[*i] - *arg, tmp, end_scope + 1))
		return (1);
	*i += length;
	return (0);
}

static int	remove_scopes(char **arg)
{
	size_t	i;
	int		to_expand;

	to_expand = 1;
	i = 0;
	while ((*arg)[i])
	{
		if ((*arg)[i] == '\'' || (*arg)[i] == '\"')
		{
			to_expand = 0;
			if (remove_scope(arg, &i))
			{
				free(*arg);
				*arg = NULL;
				return (0);
			}
		}
		else
			i++;
	}
	return (to_expand);
}

int	init_here_doc(t_file *file)
{
	char	**arg;

	arg = (char **)&file->args->content;
	file->here_doc_to_expand = remove_scopes(arg);
	return (*arg == NULL);
}
