/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 21:27:43 by ehode             #+#    #+#             */
/*   Updated: 2025/12/01 17:40:40 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "libft.h"
# include "ctx.h"

char	*get_input(t_ctx *ctx);
void	safe_exit(t_ctx **ctx, char *message);
int		is_blank(char *s);
char	is_in_scope(char c);
int		bounded_join(char **origin, size_t n, char *value, char *end);

// Path
char	*path_tilde_expand(char *path, t_dict *env);
char	*path_tilde_collapse(char *path, t_dict *env);

#endif
