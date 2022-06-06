/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_brackets.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:32:07 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/06 19:49:17 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_tree	*parse_input_brackets(const char *input, int input_size)
{
	int	i;

	i = 0;
	while (input[i] == ' ')
		i++;
	input += i + 1;
	input_size -= i + 1;
	i = input_size - 1;
	while (input[i] == ' ')
		i--;
	input_size = i;
	return (parse_input(input, input_size));
}
