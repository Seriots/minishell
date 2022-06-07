/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_to.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 14:25:26 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/07 14:26:27 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "minishell.h"

void	skip_to(const char *arg, const char *input, int input_size, int *i)
{
	skip_whitespaces(input, input_size, i);
	while (*i < input_size)
	{
		if (is_argument_equal_to(arg, input, input_size, *i))
			break ;
		skip_to_next_argument(input, input_size, i);
	}
}
