/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dict_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 06:09:29 by ehode             #+#    #+#             */
/*   Updated: 2025/11/02 07:59:32 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dict_node	*ft_dict_set(t_dict *dict, const char *key, void *value)
{
	t_dict_node	*node;

	node = ft_dict_get_node(dict, key);
	if (node)
	{
		node->value = value;
		return (node);
	}
	node = malloc(sizeof(t_dict_node));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	node->value = value;
	node->next = dict->entry;
	dict->entry = node;
	return (node);
}
