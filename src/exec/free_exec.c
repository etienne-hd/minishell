/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 00:55:37 by ehode             #+#    #+#             */
/*   Updated: 2025/12/03 02:01:45 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include "parsing.h"

void	free_exec(t_exec **exec)
{
	ft_lstclear(&(*exec)->files, clear_file);
	ft_lstclear(&(*exec)->processes, clear_process);
	free(*exec);
	*exec = NULL;
}
