/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_token_chain.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:12:04 by ncorrear          #+#    #+#             */
/*   Updated: 2025/11/28 12:31:49 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_pipe	*get_pipe_element()
{
	t_pipe *pipe;

	pipe = malloc(sizeof(t_pipe));
	if (pipe != NULL)
	{
		pipe->raw_content = ft_strndup("|", 1);
		if (pipe->raw_content == NULL)
			clear_pipe((void **) &pipe);
	}
	return (pipe);
}

static char	*get_redirect_content(t_redirect_type type)
{
	char	*content;

	if (type == REDIRECT_IN)
		content = ft_strndup("<", 1);
	else if (type == REDIRECT_HERE_DOC)
		content = ft_strndup("<<", 2);
	else if (type == REDIRECT_OUT)
		content = ft_strndup(">", 1);
	else if (type == REDIRECT_OUT_APPEND)
		content = ft_strndup(">>", 2);
	return (content);
}

static t_redirect	*get_redirect_element(char *str)
{
	t_redirect		*redirection;
	t_redirect_type	type;

	redirection = malloc(sizeof(t_redirect));
	if (redirection == NULL)
		return (redirection);
	if (str[0] == '<')
	{
		type = REDIRECT_IN;
		if (str[1] == '<')
			type = REDIRECT_HERE_DOC;
	}
	else if (str[0] == '>')
	{
		type = REDIRECT_OUT;
		if (str[1] == '>')
			type = REDIRECT_OUT_APPEND;
	}
	redirection->raw_content = get_redirect_content(type);
	redirection->redirect_type = type;
	if (redirection->raw_content == NULL)
		clear_redirection((void **) &redirection);
	return (redirection);
}

static int	is_reserved_carac(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

static t_txt	*get_txt_element(char *str)
{
	int		i;
	char	*content;
	char	stop_car;
	t_txt	*txt;

	txt = malloc(sizeof(t_txt));
	if (txt == NULL)
		return (txt);
	i = 0;
	stop_car = ' ';
	if (str[i] == '\'' || str[i] == '\"')
		stop_car = str[i++];
	while (str[i] && str[i] != stop_car && !is_reserved_carac(str[i]))
		i++;
	if (str[i] == stop_car && (stop_car == '\'' || stop_car == '\"'))
		i++;
	content = ft_strndup(str, i);
	if (content == NULL)
	{
		free(txt);
		return (NULL);
	}
	txt->expand_content = NULL;
	txt->raw_content = content;
	txt->is_to_expand = (stop_car != '\'');
	return (txt);
}

/**
 * @brief Generate a chained list with all pre_token element
 * (redirect, pipe, txt)
 *
 * @param str string to parse
 * @return chained list allocated
 */
t_tokenised_list	*get_pre_token_list(char *str)
{
	int					i;
	t_tokenised_list	*token_list;
	void				*current_element;
	int					error_occured;
	t_token				current_token;

	i = 0;
	token_list = NULL;
	error_occured = 0;
	while (str[i] && !error_occured)
	{
		if (ft_isspace(str[i]))
		{
			i++;
			continue;
		}
		else if (str[i] == '<' || str[i] == '>')
		{
			current_element = get_redirect_element(&str[i]);
			current_token = REDIRECTION;
			i += ft_strlen(((t_redirect *)current_element)->raw_content);
		}
		else if (str[i] == '|')
		{
			current_element = get_pipe_element();
			current_token = PIPE;
			i += ft_strlen(((t_pipe *)current_element)->raw_content);
		}
		else
		{
			current_element = get_txt_element(&str[i]);
			current_token = TXT;
			i += ft_strlen(((t_txt *)current_element)->raw_content);
		}
		if (!current_element)
			error_occured = 1;
		if (add_to_token_list(&token_list, current_element, current_token))
			error_occured = 1;
	}
	if (error_occured)
		clear_pre_token_list(&token_list);
	return (token_list);
}

