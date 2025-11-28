/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_pre_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:22:10 by ncorrear          #+#    #+#             */
/*   Updated: 2025/11/28 14:32:47 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	clear_pre_token(void *ptr)
{
	t_pre_token	*token;

	if (ptr == NULL)
		return ;
	token = (t_pre_token *)ptr;
	free((token)->raw_content);
	free(token);
}
