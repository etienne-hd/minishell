/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 16:16:44 by ehode             #+#    #+#             */
/*   Updated: 2025/12/06 16:36:55 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <signal.h>

void	set_process_signal_handler(void)
{
	signal(SIGINT, process_handle_signal);
	signal(SIGQUIT, SIG_IGN);
}

void	set_heredoc_signal_handler(void)
{
	signal(SIGINT, heredoc_handle_signal);
	signal(SIGQUIT, SIG_IGN);
}

void	set_default_signal_handler(void)
{
	signal(SIGINT, default_handle_signal);
	signal(SIGQUIT, SIG_IGN);
}
