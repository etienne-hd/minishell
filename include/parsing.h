/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:09:59 by ehode             #+#    #+#             */
/*   Updated: 2025/12/03 02:00:47 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "ctx.h"
# include "libft.h"
# include "exec.h"
# include "token.h"
# include <stdlib.h>

t_exec		*parse(char *input, t_ctx *ctx);

// Syntax Checker
int			is_valid_scope(char *s, t_ctx *ctx);
int			check_syntax(t_list *token_lst, t_ctx *ctx);

// Pre-Token
typedef struct s_pre_token
{
	t_token_type	type;
	char			*raw_content;
}				t_pre_token;

t_list		*get_pre_token_list(char *str);
void		clear_pre_token(void *pre_token);
int			is_reserved_char(char c);
size_t		get_text_length(char *text);

typedef struct s_token
{
	t_token_type	type;
	t_list			*args;
}				t_token;

t_list		*get_token_list(t_list *pre_token_list);
t_list		*get_arg(t_pre_token *pre_token);
void		clear_token(void *ptr);
void		clear_token_keep_cmd_arg(void *ptr);

// Expander
int			expand_tokens(t_list *tokens, t_ctx *ctx);
int			expand(t_token *token, t_ctx *ctx);
t_list		*expand_arg(char *arg, t_ctx *ctx);
char		*n_expand(char *s, size_t n, t_ctx *ctx);
t_list		*split_outscope(t_list *last_arg, size_t *i, size_t n);
int			handle_tilde(char **s);

// Joiner
void		join_args_cmd(t_list *token_lst);

// Parsing Exec init
char		*get_cmd_path(char *command, t_ctx *ctx);
void		clear_process(void *ptr);
void		clear_process_keep_args(void *ptr);
void		clear_file(void *ptr);
t_process	*init_process(t_token *token, t_ctx *ctx);
t_exec		*init_exec(t_list *token_list, t_ctx *ctx);
int			is_redirection(t_token *token);

#endif
