/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 18:04:05 by ehode             #+#    #+#             */
/*   Updated: 2025/12/01 20:14:56 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

/**
 * @brief Split the content of the last_arg lst, 0-i into last_arg and i-end into
 * a seconde node placed next to the last_arg
 *
 * @param last_arg last args -> one to split
 * @param i index where split
 * @return 0 / 1 in error case free element created inside but not outside
 */
static int	add_split_list(t_list	*last_arg, size_t *i)
{
	t_list	*new_elem;
	char	*current_split;
	char	*tmp;
	char	*tmp2;

	tmp = last_arg->content;
	current_split = ft_strndup(tmp, *i);
	if (current_split == NULL)
		return (-1);
	tmp2 = last_arg->content;
	last_arg->content = current_split;
	while (ft_isspace(tmp2[*i]))
		(*i)++;
	tmp = ft_strdup(&tmp2[*i]);
	free(tmp2);
	new_elem = ft_lstnew(tmp);
	if (tmp == NULL || new_elem == NULL)
	{
		free(tmp);
		ft_lstdelone(new_elem, clear_arg);
		return (1);
	}
	ft_lstadd_back(&last_arg, new_elem);
	return (0);
}

/**
 * @brief Split the given t_list by space and look for split from given index
 * and read for the split n carac after the i
 *
 * @param last_arg t_list to split in 2 t_list (if spaces)
 * @param i index where start reading
 * @param n number of char to read
 * @return new last_arg / NULL if malloc failed
 */
t_list	*split_outscope(t_list *last_arg, size_t *i, size_t n)
{
	char	*tmp;

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
			break ;
		if (add_split_list(last_arg, i))
			return (NULL);
		n -= *i;
		*i = 0;
		last_arg = ft_lstlast(last_arg);
		tmp = last_arg->content;
	}
	return (last_arg);
}
