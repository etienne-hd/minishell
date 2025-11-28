/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_pre_token_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:15:54 by ncorrear          #+#    #+#             */
/*   Updated: 2025/11/28 10:31:14 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
		if ((*lst)->type == PIPE || (*lst)->type == REDIRECTION)
			free((*lst)->element);
		else if ((*lst)->type == TXT)
			clear_txt(&(*lst)->element);
		free(*lst);
		*lst = tmp;
	}

	*lst = NULL;
}
