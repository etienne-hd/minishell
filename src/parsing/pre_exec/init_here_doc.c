/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:43:49 by ncorrear          #+#    #+#             */
/*   Updated: 2025/12/04 22:16:38 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include "utils.h"
#include <stddef.h>

static int	remove_scope(char **arg)
{
	size_t	i;
	char	*end_scope;
	char	*tmp;
	int		to_expand;
	size_t	length;
	
	to_expand = 1;
	i = 0;
	while ((*arg)[i])
	{
		if ((*arg)[i] == '\'' || (*arg)[i] == '\"')
		{
			to_expand = 0;
			end_scope = ft_strchr(&(*arg)[i + 1], (*arg)[i]);
			tmp = ft_strndup(&(*arg)[i + 1], end_scope - &(*arg)[i + 1]);
			if (!tmp)
			{
				free(*arg);
				*arg = NULL;
				return (0);
			}
			length = ft_strlen(tmp);
			if (!tmp || bounded_join(arg, &(*arg)[i] - *arg, tmp, end_scope + 1))
				break ;
			i += length;
		}
		else
			i++;
	}
	printf("DEBUG: %s; to_expand: %d\n", *arg, to_expand);
	return (to_expand);
}

int	init_here_doc(t_file *file)
{
	char	**arg;

	arg = (char **)&file->args->content;
	file->here_doc_to_expand = remove_scope(arg);
	return (*arg == NULL);
}
