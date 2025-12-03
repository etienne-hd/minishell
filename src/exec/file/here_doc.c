/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 23:03:51 by ehode             #+#    #+#             */
/*   Updated: 2025/12/03 00:40:02 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include "ctx.h"
#include "parsing.h"
#include <readline/readline.h>
#include <unistd.h>
#include <stdio.h>

static int	ft_strcmp_endl(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] != '\n' && s1[i] == s2[i])
		i++;
	if ((s1[i] == '\0' && s2[i] == '\n') || (s1[i] == '\n' && s2[i] == '\0'))
		return (0);
	return (ft_strcmp(s1, s2));
}

static char	*get_line(char *delimiter, t_ctx *ctx)
{
	char	*line;
	char	*tmp;

	line = readline("> ");
	if (!line)
	{
		ft_dprintf(2, "minishell: warning: here-document \
delimited by end-of-file (wanted '%s')\n", delimiter);
		return (NULL);
	}
	if (ft_strcmp_endl(line, delimiter) == 0)
	{
		free(line);
		return (NULL);
	}
	tmp = line;
	line = n_expand(line, ft_strlen(line), ctx);
	free(tmp);
	if (!line)
	{
		ft_dprintf(2, "Error\nMalloc failed.\n", delimiter);
		return (NULL);
	}
	return (line);
}

int	here_doc(char *delimiter, t_ctx *ctx)
{
	char	*line;
	int		fds[2];

	if (pipe(fds) == -1)
	{
		printf("%s: Pipe failed\n", delimiter);
		return (-1);
	}
	while (1)
	{
		line = get_line(delimiter, ctx);
		if (!line)
			break;
		write(fds[1], line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(fds[1]);
	return (fds[0]);
}
