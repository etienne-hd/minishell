/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 22:31:46 by ehode             #+#    #+#             */
/*   Updated: 2025/11/28 13:57:58 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ctx.h"
#include "utils.h"

void	safe_exit(t_ctx **ctx, char *message)
{
	ft_dprintf(2, "Error\n%s\n", message);
	destroy_ctx(ctx);
	exit(1);
}
