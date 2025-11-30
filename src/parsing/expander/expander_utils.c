/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 18:04:05 by ehode             #+#    #+#             */
/*   Updated: 2025/11/30 22:13:33 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include <stdlib.h>
#include <threads.h>

static int	add_split_list(t_list	*last_arg, char *current_split, size_t *i)
{
	t_list	*new_elem;
	char	*tmp;
	char	*tmp2;

	tmp = last_arg->content;
	current_split = ft_strndup(tmp, *i);
	if (current_split == NULL)
		return (-1);// free a list
	tmp2 = last_arg->content;
	last_arg->content = current_split;
	while (ft_isspace(tmp2[*i]))
		(*i)++;
	tmp = ft_strdup(&tmp2[*i]);
	free(tmp2);
	new_elem = ft_lstnew(tmp);
	if (tmp == NULL || new_elem == NULL)
		;// couscous
	ft_lstadd_back(&last_arg, new_elem);
	return (0);
}

t_list	*split_outscope(t_list *last_arg, size_t *i, size_t n)
{
	char	*tmp;

	//if (*i != 0)
	//	add_split_list(last_arg, last_arg->content, i);
	last_arg = ft_lstlast(last_arg);
	n += *i;
	tmp = last_arg->content;
	while (tmp[*i])
	{
		while (ft_isspace(tmp[*i]) && *i < n)
			(*i)++;
		while ((tmp[*i] && !ft_isspace(tmp[*i])) && *i < n)
			(*i)++;
		if (tmp[*i] == 0 || *i >= n)
			break;
		add_split_list(last_arg, last_arg->content, i);
		n -= *i;
		*i = 0;
		last_arg = ft_lstlast(last_arg);
		tmp = last_arg->content;
	}
	return (last_arg);
}