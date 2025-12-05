/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 17:05:59 by ncorrear          #+#    #+#             */
/*   Updated: 2025/12/05 10:21:14 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "ft_printf.h"
#include "libft.h"
#include <stddef.h>

static void	print_node(t_dict_node *node)
{
	if (ft_strcmp(node->key, "_") == 0)
		return ;
	if (node->value != NULL)
		printf("declare -x %s=\"%s\"\n", node->key, (char *)node->value);
	else
		printf("declare -x %s\n", node->key);
}

static int	is_in_dict(t_dict_node *node, t_dict_node **dict, size_t i)
{
	size_t	j;

	j = 0;
	while (j < i && dict[j] != NULL)
	{
		if (dict[j] == node)
			return (1);
		j++;
	}
	return (0);
}

static t_dict_node	**get_ordered_dict(t_dict *origin)
{
	t_dict_node	**ordered;
	t_dict_node	*current;
	t_dict_node	*minus;
	size_t		i;

	ordered = ft_calloc(origin->size + 1, sizeof(t_dict_node *));
	if (ordered == NULL)
		return (NULL);
	i = 0;
	while (i < origin->size)
	{
		current = origin->entry;
		minus = current;
		while (current)
		{
			if (is_in_dict(minus, ordered, i))
				minus = current;
			else if (ft_strcmp(current->key, minus->key) < 0
				&& !is_in_dict(current, ordered, i))
				minus = current;
			current = current->next;
		}
		ordered[i++] = minus;
	}
	return (ordered);
}

int	print_export(t_dict *origin)
{
	t_dict_node	**ordered;
	size_t		i;

	ordered = get_ordered_dict(origin);
	if (ordered == NULL)
		return (FAILURE);
	i = 0;
	while (ordered[i])
	{
		print_node(ordered[i]);
		i++;
	}
	free(ordered);
	return (SUCCESS);
}
