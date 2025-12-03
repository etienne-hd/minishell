/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncorrear <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:54:54 by ncorrear          #+#    #+#             */
/*   Updated: 2025/12/03 15:08:18 by ncorrear         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	char	*total;

	total = calloc(1, 1000);
	getcwd(total, 1000);
	printf("%s\n", total);
}
