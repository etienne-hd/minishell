/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 16:53:58 by ehode             #+#    #+#             */
/*   Updated: 2025/11/26 21:38:38 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include "libft.h"

typedef struct s_ctx
{
	t_dict	*env;
}				t_ctx;

void	destroy_ctx(t_ctx **ctx);
t_ctx	*get_ctx(int argc, char **argv, char **envp);


#endif