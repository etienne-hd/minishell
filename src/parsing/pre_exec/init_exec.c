/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:43:49 by ncorrear          #+#    #+#             */
/*   Updated: 2025/12/04 22:11:24 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctx.h"
#include "exec.h"
#include "libft.h"
#include "parsing.h"
#include "token.h"
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Create a new process and add it into the process list of exec
 *
 * @param current_process pointer to change the current_process
 * @param current_token 
 * @param exec 
 * @param ctx 
 * @return 0 / 1 if error
 */
static int	handle_cmd(t_process **current_process, t_token *current_token,
		t_exec *exec, t_ctx *ctx)
{
	t_list	*current_process_list;

	*current_process = init_process(current_token, ctx);
	if (!*current_process)
		return (1);
	current_process_list = ft_lstnew(*current_process);
	if (current_process_list == NULL)
	{
		free((*current_process)->path);
		free((*current_process)->args);
		free(*current_process);
		return (1);
	}
	ft_lstadd_back(&exec->processes, current_process_list);
	return (0);
}

/**
 * @brief Create a file of type redirection and add it into the file list of exec
 * and change the current redirection for the current_process
 *
 * @param current_redirection pointer to change the current_redirection
 * @param current_token 
 * @param exec 
 * @return 
 */
static int	handle_redirection(t_file **current_redirection,
		t_token *current_token, t_exec *exec)
{
	t_file	*current_file;
	t_list	*current_file_list;

	current_file = ft_calloc(1, sizeof(t_file));
	if (current_file == NULL)
		return (1);
	current_file->fd = -1;
	current_file->type = current_token->type;
	current_file->args = current_token->args;
	if (current_file->type == IN_HERE_DOC && init_here_doc(current_file))
	{
		free(current_file);
		return (1);
	}
	if (current_file->type == IN_FILE || current_file->type == IN_HERE_DOC)
		current_redirection[0] = current_file;
	else
		current_redirection[1] = current_file;
	current_file_list = ft_lstnew(current_file);
	if (current_file_list == NULL)
	{
		free(current_file);
		return (1);
	}
	ft_lstadd_back(&exec->files, current_file_list);
	return (0);
}

/**
 * @brief Create a file of type pipe and add it into files list of exec
 * and change the current redirection for the current process
 *
 * @param current_process 
 * @param current_redirection pointer to change the current_redirection
 * @param exec 
 * @return 0 / 1 if error
 */
static int	handle_pipe(t_process **current_process,
		t_file **current_redirection, t_exec *exec)
{
	t_file	*current_file;
	t_list	*current_file_list;

	current_file = ft_calloc(1, sizeof(t_file));
	if (current_file == NULL)
		return (1);
	current_file->fd = PIPE_FD;
	current_file->type = PIPE;
	current_file->pipe[0] = -1;
	current_file->pipe[1] = -1;
	if (*current_process && (*current_process)->file_out == NULL)
		(*current_process)->file_out = current_file;
	ft_bzero(current_redirection, sizeof(void *) * 2);
	current_redirection[0] = current_file;
	current_file_list = ft_lstnew(current_file);
	if (current_file_list == NULL)
	{
		free(current_file);
		return (1);
	}
	ft_lstadd_back(&exec->files, current_file_list);
	*current_process = NULL;
	return (0);
}

/**
 * @brief Edit the correct variabkle based on the current token type
 *
 * @param current_token 
 * @param current_process 
 * @param current_redirection 
 * @param exec 
 * @return 0 / 1 if error
 */
static int	handle_token(t_token *current_token,
		t_process **current_process, t_file **current_redirection, t_exec *exec)
{
	if (current_token->type == CMD)
	{
		if (handle_cmd(current_process, current_token, exec, exec->ctx))
			return (1);
	}
	else if (is_redirection(current_token))
	{
		if (handle_redirection(current_redirection, current_token, exec))
			return (1);
	}
	if (*current_process)
	{
		(*current_process)->file_in = current_redirection[0];
		(*current_process)->file_out = current_redirection[1];
	}
	if (current_token->type == PIPE)
	{
		if (handle_pipe(current_process, current_redirection, exec))
			return (1);
	}
	return (0);
}

/**
 * @brief Init all the exec with process list and all files of redirection / pipe
 * (not openned)
 *
 * @param token_list 
 * @param ctx 
 * @return exec / NULL if error
 */
t_exec	*init_exec(t_list *token_list, t_ctx *ctx)
{
	t_exec		*exec;
	t_process	*current_process;
	t_file		*current_redirection[2];

	exec = ft_calloc(1, sizeof(t_exec));
	if (exec == NULL)
		return (NULL);
	exec->ctx = ctx;
	current_process = NULL;
	ft_bzero(current_redirection, sizeof(current_redirection));
	while (token_list)
	{
		if (handle_token((t_token *)token_list->content,
				&current_process, current_redirection, exec))
		{
			ft_lstclear(&exec->processes, clear_process_keep_args);
			ft_lstclear(&exec->files, free);
			free(exec);
			return (NULL);
		}
		token_list = token_list->next;
	}
	return (exec);
}
