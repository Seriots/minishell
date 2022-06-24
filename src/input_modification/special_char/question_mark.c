/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   question_mark.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgiband <lgiband@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 00:50:10 by lgiband           #+#    #+#             */
/*   Updated: 2022/06/25 00:50:47 by lgiband          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../../../include/libft.h"
#include <stdlib.h>
#include <stdio.h>

size_t	count_q_mark(size_t *i, char *return_value)
{
	*i += 2;
	return (ft_strlen(return_value));
}

size_t	replace_q_mark(size_t *i, char **new, int size, char *return_value)
{
	int	j;

	j = 0;
	while (return_value[j])
	{
		(*new)[size + j] = return_value[j];
		j ++;
	}
	*i += 2;
	return (ft_strlen(return_value));
}