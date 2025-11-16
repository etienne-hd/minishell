/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dict_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 06:07:52 by ehode             #+#    #+#             */
/*   Updated: 2025/11/02 07:59:27 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_dict_get(t_dict *dict, const char *key)
{
	t_dict_node	*node;

	node = ft_dict_get_node(dict, key);
	if (node)
		return (node->value);
	return (NULL);
}
