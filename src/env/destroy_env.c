/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 17:39:35 by ehode             #+#    #+#             */
/*   Updated: 2025/11/26 18:47:13 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

/**
 * @brief free all dynamic allocation of env dictionary
 * 
 * @param env 
 */
void	destroy_env(t_dict **env)
{
	t_dict_node	*node;
	t_dict_node	*temp;

	node = (*env)->entry;
	while (node)
	{
		temp = node;
		node = node->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
	free(*env);
	*env = NULL;
}