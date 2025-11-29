/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_chain_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 17:41:36 by ehode             #+#    #+#             */
/*   Updated: 2025/11/29 17:57:50 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

t_list	*get_arg(t_pre_token *pre_token)
{
	t_arg	*arg;
	t_list	*arg_node;

	arg = ft_calloc(1, sizeof(t_arg));
	if (!arg)
		return (NULL);
	arg->raw_content = ft_strdup(pre_token->raw_content);
	arg_node = ft_lstnew(arg);
	if (arg->raw_content == NULL || arg_node == NULL)
	{
		free(arg->raw_content);
		free(arg_node);
		free(arg);
		return (NULL);
	}
	return (arg_node);
}
