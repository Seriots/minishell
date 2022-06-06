/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:30:34 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/06 19:49:07 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

t_tree	*parse_input(const char *input, int input_size)
{
	if (is_between_brackets(input, input_size))
		return (parse_input_brackets(input, input_size));
	if (contain_or(input, input_size))
		return (parse_input_or(input, input_size));
	if (contain_and(input, input_size))
		return (parse_input_and(input, input_size));
	if (contain_pipe(input, input_size))
		return (parse_input_pipe(input, input_size));
	return (parse_input_simple(input, input_size));
}
