/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 01:04:05 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/07 01:28:09 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_arguments(const char *input, int input_size)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	skip_whitespaces(input, input_size, &i);
	while (i < input_size)
	{
		count++;
		skip_to_next_argument(input, input_size, &i);
	}
	return (count);
}
