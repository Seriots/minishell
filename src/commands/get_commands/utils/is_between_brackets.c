/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_between_brackets.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:39:27 by rgarrigo          #+#    #+#             */
/*   Updated: 2022/06/10 15:01:05 by rgarrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"
#include "minishell.h"

int	is_between_brackets(const char *input, int input_size)
{
	int	i;

	if (input_size <= 0)
		return (0);
	i = 0;
	while (i < input_size - 1 && ft_strchr(WHITESPACES, input[i]) != NULL)
		i++;
	if (input[i] != '(')
		return (0);
	i = input_size - 1;
	while (i > 0 && ft_strchr(WHITESPACES, input[i]) != NULL)
		i--;
	return (input[i] == ')');
}
