/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 21:10:27 by ehode             #+#    #+#             */
/*   Updated: 2025/12/03 16:50:10 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include <stddef.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

static char	*ft_strjoin_wrapper(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	return (res);
}

static char	*get_shell_prompt(t_ctx *ctx)
{
	char	*prompt;
	char	*pwd;
	char	*collapse_path;
	char	*user;

	prompt = ft_strdup("");
	user = ft_dict_get(ctx->env, "USER");
	if (user)
		prompt = ft_strjoin_wrapper(prompt, user);
	pwd = get_pwd();
	if (pwd)
	{
		if (user)
			prompt = ft_strjoin_wrapper(prompt, ":");
		collapse_path = path_tilde_collapse(pwd, ctx->env);
		if (collapse_path)
			prompt = ft_strjoin_wrapper(prompt, collapse_path);
		else
			prompt = ft_strjoin_wrapper(prompt, pwd);
		free(pwd);
		free(collapse_path);
	}
	prompt = ft_strjoin_wrapper(prompt, "$ ");
	return (prompt);
}

char	*get_input(t_ctx *ctx)
{
	char	*line;
	char	*prompt;

	prompt = get_shell_prompt(ctx);
	if (!prompt)
		line = readline("$ ");
	else
		line = readline(prompt);
	free(prompt);
	return (line);
}
