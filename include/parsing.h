/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:09:59 by ehode             #+#    #+#             */
/*   Updated: 2025/11/28 12:07:00 by ncorrear         ###   ########.fr       */
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
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_HERE_DOC,
	REDIRECT_OUT_APPEND,
}	t_redirect_type;

typedef struct	s_redirect
{
	t_redirect_type	redirect_type;
	char	*raw_content;
}				t_redirect;

// ? : Set element to NULL when it's a pipe ?
typedef struct	s_pipe
{
	char	*raw_content;
}				t_pipe;

typedef struct	s_txt
{
	char	*raw_content;
	int		is_to_expand;
	char	*expand_content;
}				t_txt;

int	is_valid_scope(char *s, t_ctx *ctx);
t_tokenised_list	*get_pre_token_list(char *str);

// Token management
int	add_to_token_list(t_tokenised_list **lst, void *elemt, t_token type);

// Token clearing
void	clear_txt(void **elmt);
void	clear_pipe(void **elmt);
void	clear_redirection(void **elmt);
void	clear_pre_token_list(t_tokenised_list **lst);

#endif
