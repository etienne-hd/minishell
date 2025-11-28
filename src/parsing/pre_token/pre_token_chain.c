/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_token_chain.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:12:04 by ncorrear          #+#    #+#             */
/*   Updated: 2025/11/28 15:14:09 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include <stdio.h>
#include <stdlib.h>

static t_pre_token	*get_pipe_token(void)
{
	t_pre_token	*token;

	token = ft_calloc(1, sizeof(t_pre_token));
	if (token == NULL)
		return (NULL);
	token->type = PIPE;
	token->raw_content = ft_strdup("|");
	if (token->raw_content == NULL)
	{
		free(token);
		return (NULL);
	}
	return (token);
}

static t_pre_token	*get_redirect_token(char *str)
{
	t_pre_token	*token;

	token = ft_calloc(1, sizeof(t_pre_token));
	if (token == NULL)
		return (NULL);
	if (ft_strncmp("<<", str, 2) == 0)
		token->raw_content = ft_strdup("<<");
	else if (ft_strncmp("<", str, 1) == 0)
		token->raw_content = ft_strdup("<");
	else if (ft_strncmp(">>", str, 2) == 0)
		token->raw_content = ft_strdup(">>");
	else
		token->raw_content = ft_strdup(">");
	token->type = REDIRECTION;
	if (token->raw_content == NULL)
	{
		free(token);
		return (NULL);
	}
	return (token);
}

static t_pre_token	*get_text_token(char *str)
{
	size_t		length;
	t_pre_token	*token;

	token = ft_calloc(1, sizeof(t_pre_token));
	if (token == NULL)
		return (NULL);
	length = get_text_length(str);
	token->type = TEXT;
	token->raw_content = ft_strndup(str, length);
	if (token->raw_content == NULL)
	{
		free(token);
		return (NULL);
	}
	return (token);
}

t_pre_token	*get_pre_token(char *str)
{
	t_pre_token	*token;

	if (*str == '<' || *str == '>')
		token = get_redirect_token(str);
	else if (*str == '|')
		token = get_pipe_token();
	else
		token = get_text_token(str);
	return (token);
}

/**
 * @brief Generate a chained list with all pre_token element
 * (redirect, pipe, txt)
 *
 * @param str string to parse
 * @return chained list allocated
 */
t_list	*get_pre_token_list(char *str)
{
	t_list				*token_list;
	t_list				*current_list;
	t_pre_token			*current_token;

	token_list = NULL;
	while (*str)
	{
		while (ft_isspace(*str))
			str++;
		if (*str == 0)
			break ;
		current_token = get_pre_token(str);
		if (current_token)
			str += ft_strlen(current_token->raw_content);
		current_list = ft_lstnew(current_token);
		ft_lstadd_back(&token_list, current_list);
		if (current_token == NULL || current_list == NULL)
		{
			clear_pre_token(current_token);
			ft_lstclear(&token_list, clear_pre_token);
			break ;
		}
	}
	return (token_list);
}
