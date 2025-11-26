/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 21:10:27 by ehode             #+#    #+#             */
/*   Updated: 2025/11/26 22:58:09 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stddef.h>
#include <stdio.h>

static void	show_shell_prompt(t_ctx *ctx)
{
	char	*pwd;
	char	*collapse_path;
	char	*user;

	user = ft_dict_get(ctx->env, "USER");
	if (user)
		printf("%s", user);
	pwd = ft_dict_get(ctx->env, "PWD");
	if (pwd)
	{
		if (user)
			printf(":");
		collapse_path = path_tilde_collapse(pwd, ctx->env);
		if (collapse_path)
		{
			printf("%s", collapse_path);
			free(collapse_path);
		}
		else
			printf("%s", pwd);
	}
	printf("$ ");
}

char	*get_input(t_ctx *ctx)
{
	char	*buffer;
	size_t	size;

	size = 4096;
	buffer = malloc(size * sizeof(char));
	if (!buffer)
		return (NULL);
	show_shell_prompt(ctx);
	if (getline(&buffer, &size, stdin) == -1)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}
