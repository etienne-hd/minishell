/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 23:03:51 by ehode             #+#    #+#             */
/*   Updated: 2025/12/06 16:34:31 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ctx.h"
#include "parsing.h"
#include "utils.h"
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

/**
 * @brief read_user input of the here_doc and expand var in it
 *
 * @param delimiter stop word of the here_doc
 * @param ctx 
 * @return 
 */
static char	*get_line(char *delimiter, int to_expand, t_ctx *ctx)
{
	char	*line;
	char	*tmp;

	line = readline("> ");
	if (!line && (g_signal != 2))
	{
		ft_dprintf(2, "minishell: warning: here-document \
delimited by end-of-file (wanted '%s')\n", delimiter);
		return (NULL);
	}
	if (g_signal == 2 || ft_strcmp_endl(line, delimiter) == 0)
	{
		free(line);
		return (NULL);
	}
	if (!to_expand)
		return (line);
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

/**
 * @brief listen to the user input writing it into a pipe until delimiter word
 *
 * @param delimiter 
 * @param ctx 
 * @return reading side fd of the pipe
 */
int	here_doc(char *delimiter, int to_expand, t_ctx *ctx)
{
	char	*line;
	int		fds[2];
	int		dup_stdin;

	if (pipe(fds) == -1)
	{
		ft_dprintf(2, "%s: Pipe failed\n", delimiter);
		return (-1);
	}
	dup_stdin = dup(0);
	while (1)
	{
		set_heredoc_signal_handler();
		line = get_line(delimiter, to_expand, ctx);
		if (!line)
			break ;
		write(fds[1], line, ft_strlen(line));
		write(fds[1], "\n", 1);
		free(line);
	}
	dup2(dup_stdin, 0);
	free(line);
	close_fd(&dup_stdin);
	close_fd(&fds[1]);
	return (fds[0]);
}
