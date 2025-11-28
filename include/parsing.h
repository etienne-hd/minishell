/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:09:59 by ehode             #+#    #+#             */
/*   Updated: 2025/11/28 15:15:47 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "ctx.h"

typedef enum e_token
{
	REDIRECTION,
	PIPE,
	TEXT,
\
	CMD,
	IN_FILE,
	IN_HERE_DOC,
	OUT_FILE,
	OUT_FILE_APPEND,
}				t_token;

typedef struct s_pre_token
{
	t_token	type;
	char	*raw_content;
}				t_pre_token;

int		parse(char *input, t_ctx *ctx);

int		is_valid_scope(char *s, t_ctx *ctx);

// Pre-Token
t_list	*get_pre_token_list(char *str);
void	clear_pre_token(void *pre_token);
int		is_reserved_char(char c);
size_t	get_text_length(char *text);

// Token

#endif
