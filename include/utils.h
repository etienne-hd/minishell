/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 21:27:43 by ehode             #+#    #+#             */
/*   Updated: 2025/11/30 22:45:29 by ncorrear         ###   ########.fr       */
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

// Convert no malloc
char	*ft_ulltoa(unsigned long long nbr);

#endif
