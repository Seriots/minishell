/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argument_after.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 00:33:56 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/07 01:53:18 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_argument_after(const char *arg, const char *input, int input_size)
{
	int	i;

	i = 0;
	skip_whitespaces(input, input_size, &i);
	while (1)
	{
		if (i >= input_size)
			return (-1);
		if (is_argument_equal_to(arg, input, input_size, i))
			break ;
		skip_to_next_argument(input, input_size, &i);
	}
	skip_to_next_argument(input, input_size, &i);
	return (get_argument(input, input_size, i));
}
