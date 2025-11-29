/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dict_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 06:19:01 by ehode             #+#    #+#             */
/*   Updated: 2025/11/29 18:06:31 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free_node(t_dict_node *node)
{
	free(node->key);
	free(node);
}

void	ft_dict_unset(t_dict *dict, const char *key)
{
	t_dict_node	*node;
	t_dict_node	*temp_node;

	node = dict->entry;
	if (node && !ft_strcmp(node->key, key))
	{
		dict->size--;
		dict->entry = node->next;
		ft_free_node(node);
		return ;
	}
	while (node && node->next)
	{
		temp_node = node->next;
		if (!ft_strcmp(temp_node->key, key))
		{
			dict->size--;
			node->next = temp_node->next;
			ft_free_node(temp_node);
			return ;
		}
		node = node->next;
	}
}
