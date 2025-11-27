/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 21:27:43 by ehode             #+#    #+#             */
/*   Updated: 2025/11/27 13:47:58 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "libft.h"
# include "ctx.h"

char	*get_input(t_ctx *ctx);
void	safe_exit(t_ctx **ctx, char *message);
int		is_blank(char *s);

// Path
char	*path_tilde_expand(char *path, t_dict *env);
char	*path_tilde_collapse(char *path, t_dict *env);

#endif