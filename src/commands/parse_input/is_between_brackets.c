/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_between_brackets.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:39:27 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/06 19:43:20 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_between_brackets(const char *input, int input_size)
{
	int	i;

	i = 0;
	if (input_size <= 0)
		return (0);
	while (i < input_size - 1 && input[i] == ' ')
		i++;
	if (input[i] != '(')
		return (0);
	i = input_size - 1;
	while (i >= 0 && input[i] == ' ')
		i--;
	return (input[i] == ')');
}
