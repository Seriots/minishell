/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_argument_in_input.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 22:00:30 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/07 01:53:01 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	is_argument_in_input(const char *arg, const char *input, int input_size)
{
	int	i;

	skip_whitespaces(input, input_size, &i);
	i = 0;
	while (1)
	{
		if (i >= input_size)
			return (0);
		if (is_argument_equal_to(arg, input, input_size, i))
			return (1);
		skip_to_next_argument(input, input_size, &i);
	}
}
