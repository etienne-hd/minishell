/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_token_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:22:10 by ncorrear          #+#    #+#             */
/*   Updated: 2025/11/28 12:14:14 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	clear_txt(void **elmt)
{
	t_txt	**txt;

	txt = (t_txt **)elmt;
	free((*txt)->raw_content);
	free((*txt)->expand_content);
	free(*elmt);
	*elmt = NULL;
}

void	clear_pipe(void **elmt)
{
	t_pipe	**pipe;

	pipe = (t_pipe **)elmt;
	free((*pipe)->raw_content);
	free(*elmt);
	*elmt = NULL;
}

void	clear_redirection(void **elmt)
{
	t_redirect	**redirect;

	redirect = (t_redirect **)elmt;
	free((*redirect)->raw_content);
	free(*elmt);
	*elmt = NULL;
}
