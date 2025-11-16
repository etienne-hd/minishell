/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:37:16 by ehode             #+#    #+#             */
/*   Updated: 2025/10/16 19:20:09 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first_lst;
	t_list	*current_lst;
	t_list	*temp_lst;
	void	*content;

	current_lst = NULL;
	first_lst = NULL;
	while (lst && f && del)
	{
		content = f(lst->content);
		temp_lst = ft_lstnew(content);
		if (!temp_lst)
		{
			del(content);
			ft_lstclear(&first_lst, del);
			return (NULL);
		}
		if (current_lst)
			current_lst->next = temp_lst;
		else
			first_lst = temp_lst;
		current_lst = temp_lst;
		lst = lst->next;
	}
	return (first_lst);
}
