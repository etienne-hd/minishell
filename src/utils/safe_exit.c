/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 22:31:46 by ehode             #+#    #+#             */
/*   Updated: 2025/11/26 22:55:44 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ctx.h"

void	safe_exit(t_ctx **ctx, char *message)
{
	ft_dprintf(2, "Error\n%s\n", message);
	destroy_ctx(ctx);
	exit(1);
}
