/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:09:59 by ehode             #+#    #+#             */
/*   Updated: 2025/11/30 11:29:50 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "ctx.h"
# include "libft.h"
# include <stdlib.h>

typedef enum e_token_type
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
	END,
}				t_token_type;

int		parse(char *input, t_ctx *ctx);

// Syntax Checker
int		is_valid_scope(char *s, t_ctx *ctx);
int		check_syntax(t_list *token_lst, t_ctx *ctx);

// Pre-Token
typedef struct s_pre_token
{
	t_token_type	type;
	char			*raw_content;
}				t_pre_token;

t_list	*get_pre_token_list(char *str);
void	clear_pre_token(void *pre_token);
int		is_reserved_char(char c);
size_t	get_text_length(char *text);

// Token
typedef struct s_arg
{
	int		is_expanded;
	char	*raw_content;
	char	*arg;
}				t_arg;

typedef struct s_token
{
	t_token_type	type;
	t_list			*args;
}				t_token;

t_list	*get_token_list(t_list *pre_token_list);
t_list	*get_arg(t_pre_token *pre_token);
void	clear_arg(void *ptr);
void	clear_token(void *ptr);

// Expansion
char	*get_expanded_arg(char	*arg, t_ctx *ctx);

#endif
