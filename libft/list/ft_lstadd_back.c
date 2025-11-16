/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:06:34 by ehode             #+#    #+#             */
/*   Updated: 2025/10/16 19:04:59 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current_lst;

	if (!lst || !new)
		return ;
	current_lst = *lst;
	if (!current_lst)
	{
		*lst = new;
		return ;
	}
	while (current_lst && current_lst->next)
		current_lst = current_lst->next;
	current_lst->next = new;
}
