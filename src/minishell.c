/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 16:53:30 by ehode             #+#    #+#             */
/*   Updated: 2025/11/28 12:18:22 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "utils.h"
#include "parsing.h"
#include <readline/history.h>
#include <readline/readline.h>

static void	print_token_lst(t_tokenised_list *lst)
{
	while (lst)
	{
		if (lst->type == REDIRECTION)
			ft_printf("Redirection: {content: %s}\n", ((t_redirect *)(lst->element))->raw_content);
		if (lst->type == PIPE)
			ft_printf("Pipe: {content: %s}\n", ((t_pipe *)(lst->element))->raw_content);
		if (lst->type == TXT)
			ft_printf("TXT: {to_expand: %i, content: %s}\n",
				((t_txt *)(lst->element))->is_to_expand,
				((t_txt *)(lst->element))->raw_content);
		lst = lst->next_element;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_ctx	*ctx;
	char	*input;
	t_tokenised_list *parsed;

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

		// TMP
		if (is_valid_scope(input, ctx))
		{
			parsed = get_pre_token_list(input);
			print_token_lst(parsed);
			free(parsed);
		}
		// printf("%d - status_code = %d\n", is_valid_scope(input, ctx), ctx->status_code);
		// printf("INPUT -> %s - LENGTH -> %zu\n", input, ft_strlen(input));
		// END TMP

		if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			break ;
		}
		free(input);
	}
	destroy_ctx(&ctx);
}
