/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 16:53:30 by ehode             #+#    #+#             */
/*   Updated: 2025/11/26 22:39:27 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "utils.h"
#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	t_ctx	*ctx;
	char	*input;

	ctx = get_ctx(argc, argv, envp);
	if (!ctx)
		return (1);
	while (1)
	{
		input = get_input(ctx);
		if (!input)
			break;
		// TMP
		printf("INPUT -> %s", input);
		if (ft_strcmp(input, "exit\n") == 0)
		{
			free(input);	
			break;
		}
		free(input);
	}
	destroy_ctx(&ctx);
}
