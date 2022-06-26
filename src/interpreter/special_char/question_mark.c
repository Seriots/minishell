/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   question_mark.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 00:50:10 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/26 14:35:22 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../../../include/libft.h"
#include <stdlib.h>
#include <stdio.h>

size_t	count_q_mark(size_t *i, char *return_value)
{
	size_t	size;

	*i += 2;
	if (!return_value)
		return (0);
	size = ft_strlen(return_value);
	free (return_value);
	return (size);
}

size_t	replace_q_mark(size_t *i, char **new, int size, char *return_value)
{
	int		j;
	size_t	size_r_val;

	j = 0;
	*i += 2;
	if (!return_value)
		return (0);
	while (return_value[j])
	{
		(*new)[size + j] = return_value[j];
		j ++;
	}
	size_r_val = ft_strlen(return_value);
	free (return_value);
	return (size_r_val);
}
