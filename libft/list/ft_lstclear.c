/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:18:26 by ehode             #+#    #+#             */
/*   Updated: 2025/11/02 20:55:06 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current_lst;
	t_list	*temp_lst;

	if (!lst)
		return ;
	current_lst = *lst;
	while (current_lst)
	{
		temp_lst = current_lst;
		current_lst = current_lst->next;
		if (del)
			del(temp_lst->content);
		free(temp_lst);
	}
	*lst = NULL;
}
