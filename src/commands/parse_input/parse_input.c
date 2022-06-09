/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:30:34 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/09 03:29:43 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

t_tree	*parse_input(const char *input, int input_size)
{
	if (is_between_brackets(input, input_size))
		return (parse_input_brackets(input, input_size));
	if (is_argument_in_input(OR, input, input_size))
		return (parse_input_or(input, input_size));
	if (is_argument_in_input(AND, input, input_size))
		return (parse_input_and(input, input_size));
	if (is_argument_in_input(PIPE, input, input_size))
		return (parse_input_pipe(input, input_size));
	return (parse_input_simple(input, input_size));
}
