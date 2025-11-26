/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 17:39:35 by ehode             #+#    #+#             */
/*   Updated: 2025/11/26 18:43:53 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include <stddef.h>

static char	*get_value(char *raw)
{
	char	*start_value;
	char	*end_value;
	char	*value;

	end_value = ft_strchr(raw, 0);
	start_value = ft_strchr(raw, '=') + 1;
	value = ft_strndup(start_value, end_value - start_value);
	return (value);
}

static char	*get_key(char *raw)
{
	char	*end_key;
	char	*key;

	end_key = ft_strchr(raw, '=');
	key = ft_strndup(raw, end_key - raw);
	return (key);
}
/**
 * @brief load envp into a parsed structured dictionary
 * 
 * @param envp 
 * @return t_dict* 
 */
t_dict	*load_env(char **envp)
{
	size_t	i;
	t_dict	*env;
	char	*key;
	char	*value;

	env = ft_dict_new();
	if (!env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		key = get_key(envp[i]);
		value = get_value(envp[i]);
		if (!key || !value || !ft_dict_set(env, key, value))
		{
			free(key);
			free(value);
			destroy_env(&env);
			return (NULL);
		}
		free(key);
		i++;
	}
	return (env);
}
