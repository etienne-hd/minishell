/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_managment.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:15:54 by ncorrear          #+#    #+#             */
/*   Updated: 2025/11/28 12:04:56 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	add_to_token_list(t_tokenised_list **lst, void *elemt, t_token type)
{
	t_tokenised_list	*current;
	t_tokenised_list	*new_elemt;

	new_elemt = malloc(sizeof(t_tokenised_list));
	if (new_elemt == NULL)
		return (1);
	new_elemt->next_element = NULL;
	new_elemt->element = elemt;
	new_elemt->type = type;
	if (*lst == NULL)
		*lst = new_elemt;
	else
	{
		current = *lst;
		while (current && current->next_element)
			current = current->next_element;
		current->next_element = new_elemt;
	}
	return (0);
}

/**
 * @brief Free all element of a pre_tokenesied chained list + set list to NULL
 *
 * @param lst 
 */
void	clear_pre_token_list(t_tokenised_list **lst)
{
	t_tokenised_list	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next_element;
		if ((*lst)->type == PIPE)
			clear_pipe(&(*lst)->element);
		else if ((*lst)->type == REDIRECTION)
			clear_redirection(&(*lst)->element);
		else if ((*lst)->type == TXT)
			clear_txt(&(*lst)->element);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}
