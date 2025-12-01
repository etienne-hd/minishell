/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 16:53:30 by ehode             #+#    #+#             */
/*   Updated: 2025/11/30 22:09:40 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "libft.h"
#include "utils.h"
#include "parsing.h"
#include <readline/history.h>
#include <readline/readline.h>

// int	main(int argc, char **argv, char **envp)
// {
// 	t_ctx	*ctx;
// 	t_list	*args;
// 	char	*ta_daronne;
// 	char	*input;
//
// 	ctx = init_ctx(argc, argv, envp);
// 	if (!ctx)
// 		return (1);
// 	input = get_input(ctx);
// 	ta_daronne = ft_strdup(input);
// 	args = expand_arg(ta_daronne, ctx);
// 	while (args)
// 	{
// 		printf("[%s]\n", (char *)args->content);
// 		args = args->next;
// 	}
// 	destroy_ctx(&ctx);
// }

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
		if (is_blank(input))
			continue ;
		add_history(input);
		parse(input, ctx);
		if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			break ;
		}
		free(input);
	}
	destroy_ctx(&ctx);
}

