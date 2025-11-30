/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_chain_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 17:41:36 by ehode             #+#    #+#             */
/*   Updated: 2025/11/30 15:31:02 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

t_list	*get_arg(t_pre_token *pre_token)
{
	char	*arg;
	t_list	*arg_node;

	arg = ft_strdup(pre_token->raw_content);
	arg_node = ft_lstnew(arg);
	if (arg == NULL || arg_node == NULL)
	{
		free(arg);
		free(arg_node);
		return (NULL);
	}
	return (arg_node);
}
