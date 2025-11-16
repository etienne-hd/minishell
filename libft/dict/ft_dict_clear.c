/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dict_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 06:19:01 by ehode             #+#    #+#             */
/*   Updated: 2025/11/02 07:58:57 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free_node(t_dict_node *node)
{
	free(node->key);
	free(node);
}

void	ft_dict_clear(t_dict **dict)
{
	t_dict_node	*node;
	t_dict_node	*temp_node;

	node = (*dict)->entry;
	while (node)
	{
		temp_node = node;
		node = node->next;
		ft_free_node(temp_node);
	}
	free(*dict);
	*dict = NULL;
}
