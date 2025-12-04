/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:31:50 by ehode             #+#    #+#             */
/*   Updated: 2025/12/03 15:32:52 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"

char	*get_pwd(void)
{
	char	*pwd;
	char	*result;

	pwd = ft_calloc(4096 + 1, 1);
	if (pwd == NULL)
		return (NULL);
	result = getcwd(pwd, 4096 + 1);
	if (!result)
	{
		free(pwd);
		return (NULL);
	}
	return (pwd);
}
