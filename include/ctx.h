/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 22:37:55 by ehode             #+#    #+#             */
/*   Updated: 2025/12/03 17:44:39 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CTX_H
# define CTX_H

# include "libft.h"
# include <stdint.h>

typedef struct s_ctx
{
	char		**envp;
	t_dict		*env;
	uint8_t		status_code;
}				t_ctx;

void	destroy_ctx(t_ctx **ctx);
t_ctx	*init_ctx(int argc, char **argv, char **envp);

#endif