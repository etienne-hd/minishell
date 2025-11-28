/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:09:59 by ehode             #+#    #+#             */
/*   Updated: 2025/11/27 15:10:35 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "ctx.h"

// GLOBAL TYPE FOR PARSING
typedef enum	e_token
{
	REDIRECTION,
	PIPE,
	TXT,
	CMD,
	IN_FILE,
	IN_HERE_DOC,
	OUT_FILE,
	OUT_FILE_APPEND,
}				t_token;

typedef struct	s_tokenised_list
{
	t_token			type;
	void			*element;
	void			*next_element;
}				t_tokenised_list;

// PRE_SYNTAX
typedef enum	e_redirect_type
{
	IN,
	OUT,
	HERE_DOC,
	OUT_APPEND,
}	t_redirect_type;

typedef struct	s_redirect
{
	t_redirect_type	redirect_type;
	char			*raw_content;
}				t_redirect;

typedef struct	s_pipe
{
	char	*raw_content;
}				t_pipe;

typedef struct	s_txt
{
	char	*raw_content;
	int		is_to_epand;
	char	*expand_content;
}				t_txt;

int	is_valid_scope(char *s, t_ctx *ctx);

#endif
