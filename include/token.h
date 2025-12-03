/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 22:53:43 by ehode             #+#    #+#             */
/*   Updated: 2025/12/02 22:53:51 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_token_type
{
	REDIRECTION,
	PIPE,
	TEXT,
\
	CMD,
	IN_FILE,
	IN_HERE_DOC,
	OUT_FILE,
	OUT_FILE_APPEND,
	END,
}				t_token_type;

#endif