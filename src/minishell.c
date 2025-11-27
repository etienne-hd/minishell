/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 16:53:30 by ehode             #+#    #+#             */
/*   Updated: 2025/11/27 13:14:12 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "utils.h"
#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	t_ctx	*ctx;
	char	*input;

	ctx = init_ctx(argc, argv, envp);
	if (!ctx)
		safe_exit(&ctx, "Unable to init ctx.");
	while (1)
	{
		input = get_input(ctx);
		if (!input)
			safe_exit(&ctx, "Unable to retreive user input.");
		printf("INPUT -> %s - LENGTH -> %zu\n", input, ft_strlen(input));
		if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			break ;
		}
		free(input);
	}
	destroy_ctx(&ctx);
}
