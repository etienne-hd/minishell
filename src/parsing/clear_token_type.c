/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_token_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:22:10 by ncorrear          #+#    #+#             */
/*   Updated: 2025/11/28 10:31:39 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Clear correctly a t_txt token + set it to NULL
 *
 * @param elmt 
 */
void	clear_txt(void **elmt)
{
	t_txt	**txt;

	txt = (t_txt **)elmt;
	free((*txt)->raw_content);
	free((*txt)->expand_content);
	*txt = NULL;
}
